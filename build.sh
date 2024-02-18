#!/bin/sh
rm -rf bin
mkdir bin
cmake .
make
rm nogrw0write.skprx.out
rm nogrw0write
rm nogrw0write.velf
mv nogrw0write.skprx bin