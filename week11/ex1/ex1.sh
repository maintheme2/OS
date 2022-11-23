#!/bin/sh
fallocate --length 50M lofs.img
sudo losetup -f lofs.img
mkdir lofsdisk
sudo mkfs.ext4 /dev/loop0 
sudo mount -o loop /dev/loop0 lofsdisk/
sudo chown $USER:$USER lofsdisk
