#!/bin/sh
rm ex3.txt
gcc ex3.c
for i in 1 2 4 10 100
do
    echo "m = $i" >> ex3.txt
    { time sh -c "$(pwd)/a.out 10000000 $i" ; } 2>> ex3.txt 
    echo "" >> ex3.txt
done
rm a.out