#! /bin/sh

mkdir root
date
sleep 3
ls -tr / > root/root.txt
date
sleep 3
mkdir home
date
sleep 3
ls -tr ~ > home/home.txt

cat root/root.txt
cat home/home.txt
ls root
ls home
