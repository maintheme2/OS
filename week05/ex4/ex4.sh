#!/bin/sh
rm ex4.txt
gcc ex4.c
for i in 1 2 4 10 100
do
    echo "m = $i" >> ex4.txt
    { time sh -c "$(pwd)/a.out 10000000 $i" ; } 2>> ex4.txt 
    echo "" >> ex4.txt
done
rm a.out