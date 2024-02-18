# NoGrw0Write

This kernel plugin prevent the system from writing to a game cart's writable partition (grw0). It does that by:

- Preventing the system from mounting the grw0 partition.
- Preventing block device `sdstor0:gcd-lp-ign-gamerw` from being opened. (for stuff writing directly to block devices.)

## Disclaimer

**THIS PLUGIN IS DISTRIBUTED AS-IS THE AUTHOR CANNOT BE HELD RESPONSIBLE FOR ANY DAMAGE TO THE DEVICE OR LOST OF DATA THAT MIGHT
OCCUR FOLLOWING THE USAGE OF THIS PLUGIN. USE THIS AT YOUR OWN RISK!**

With that out of the way, I can say that I've tested this on my device without any problem. It is possible however that 
it might not play nice with other plugins on your device. I can't test every environment possible.

The code is pretty minimalistic and doesn't write to anything so it should be pretty harmless but I don't guarantee anything.

If your PSVita ever Freeze on boot, hold down the power button for 30 seconds, you will boot into safe mode. Just select 
restart the device, try this at most maybe 5 times. If it still freezes, restart it again with safeboot this time holding
the left trigger this will boot the system without loading plugins, follow the instruction to disable the plugin below and reboot.

If it won't boot even with the left trigger pressed then consider doing a restore using the safe boot menu. You will have
to reinstall henkaku ensou.

## Installation

- Copy nogrw0write.skprx to `ur0:tai`  
- Add the following lines to either `ur0:tai/config.txt` or `ux0:tai/config.txt`
```
*KERNEL
ur0:tai/nogrw0write.skprx
```

- For maximum compatibility add these line as far up in the file as you can.
- Reboot your vita.

## Disabling the plugin

- Open your taihen config file. (either `ur0:tai/config.txt` or `ux0:tai/config.txt`)
- comment out the line you added at the installation step by adding a '#' at the front of the line `#ur0:tai/nogrw0write.skprx`
- Reboot
- If you want to re-enable it later then you just have to repeat the same process but remove the '#' at the start of the line and reboot.

## Uninstalling

- Remove the lines added to your taihen config in the installation step.
- Remove `ur0:tai/nogrw0write.skprx`
- Reboot

## Warning

Disable this plugin when you want to play a game with a grw0: partition. If you try to play a grw0: game with this enabled the game will
either not install at all or crash at launch. You also need to disable this plugin if you want to browse the grw0: in vitashell.

## Known issues

For this plugin to be effective you have to insert your game cart **AFTER** booting the console. I believe this is because the system has a chance to mount the partition before the plugin kicks in.

## Credits

- The No-Intro community: For giving me advices and guidance and just being awesome for the preservation of video games.
- The Henkaku community: For helping me with coding tips and suggestions even when I ask n00b questions (I am a n00b wrt vita programming)
- Yifan Lu: For henkaku/taihen thank you!
- SKGleba: For vitadeploy and a lot of other cool tools.
- TheFloW: For vitashell and a lot of other cool tools.