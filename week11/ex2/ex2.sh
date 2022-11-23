#!/bin/sh
echo "Oleg" > lofsdisk/file1
echo "Hlopcev" > lofsdisk/file2
mkdir lofsdisk/bin lofsdisk/lib lofsdisk/lib64 lofsdisk/usr
sudo mount --bind /usr lofsdisk/usr
sudo mount --bind /lib64 lofsdisk/lib64
sudo mount --bind /lib lofsdisk/lib
sudo mount --bind /bin lofsdisk/bin
gcc ex2.c -o ex2.out
sudo cp ex2.out lofsdisk/
sudo chroot lofsdisk/
./ex2.out > ex2.txt
./ex2.out >> ex2.txt
