#!/bin/sh

touch _ex3.txt
echo "some content" > _ex3.txt
chmod -x _ex3.txt
ls -l _ex3.txt > ex3.txt
chmod uo=rwx _ex3.txt
ls -l _ex3.txt >> ex3.txt
chmod g=rwx _ex3.txt
ls -l _ex3.txt >> ex3.txt
