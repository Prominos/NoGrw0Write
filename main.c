#include <psp2kern/kernel/modulemgr.h>
#include <psp2kern/kernel/iofilemgr.h>
#include <psp2kern/kernel/debug.h>
#include <psp2kern/kernel/sysclib.h> 
#include <taihen.h>
#include <psp2kern/kernel/sysmem/data_transfers.h>
#include <psp2kern/kernel/cpu.h> 

// handle to our hook
static tai_hook_ref_t nogrw0_open_ref = 0;
static tai_hook_ref_t nogrw0_kmount_ref = 0;

SceUID no_grw0_hook_user_open(const char *path, int flags, SceMode mode, void *args) {
  char k_path[256];
  k_path[255] = 0; //just in case
  const char* grw02 = "sdstor0:gcd-lp-ign-gamerw";
  SceUID fd = -1;
  // we need to copy the user pointer to kernel space
  ksceKernelStrncpyUserToKernel(k_path, (uintptr_t)path, 256);

//check if path starts with block device name for grw0
    if (!strncmp(grw02, k_path, 25) && ((flags & SCE_O_WRONLY) != 0))
    {
        ksceDebugPrintf("[NoGrw0Write] Something is opening writable game partition: %s, File Descriptor: %x Mode: %x\n", k_path, fd, flags);
        return -1;
    }

    if (nogrw0_open_ref)
    fd = TAI_CONTINUE(SceUID, nogrw0_open_ref, path, flags, mode, args);
  
  return fd;
}

int no_grw0_hook_kernel_mount(int vshMountId, const char *path, int permission, int unk3, int arg_0, int arg_4) 
{
  int state, res;
  res = -1;
  ENTER_SYSCALL(state);
  if (vshMountId == 0xa00) {
    ksceDebugPrintf("[NoGrw0Write] Detected mounting of grw0: Denying...\n");
    permission = 1;
    EXIT_SYSCALL(state);
    //Do not mount it at all.
    return 0;
  }
  
  if (nogrw0_kmount_ref)
    res = TAI_CONTINUE(int, nogrw0_kmount_ref, vshMountId, path, permission, unk3, arg_0, arg_4);
  EXIT_SYSCALL(state);
  return res;
}

// plugin entry
int nogrw0_module_start(SceSize argc, const void *args) {
  taiHookFunctionExportForKernel(KERNEL_PID,      // Kernel process
                                 &nogrw0_open_ref,       // Output a reference
                                 "SceIofilemgr",  // Name of module being hooked
                                 TAI_ANY_LIBRARY, // If there's multiple libs exporting this
                                 0xCC67B6FD,      // NID specifying sceIoOpen
                                 no_grw0_hook_user_open); // Name of the hook function

taiHookFunctionExportForKernel(KERNEL_PID,      // Kernel process
                                 &nogrw0_kmount_ref,       // Output a reference
                                 "SceIofilemgr",  // Name of module being hooked
                                 TAI_ANY_LIBRARY, //SceIofilemgrForDriver
                                 0xD070BC48,      // NID specifying sceIoMountForDriver
                                 no_grw0_hook_kernel_mount); // Name of the hook function

  return SCE_KERNEL_START_SUCCESS;
}