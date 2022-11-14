#!/bin/sh

touch _ex3.txt
echo "some content" > _ex3.txt
chmod o-r _ex3.txt
ls -l _ex3.txt > ex3.txt
chmod ugo+r _ex3.txt
chmod ugo-w _ex3.txt
ls -l _ex3.txt >> ex3.txt
chmod g=u _ex3.txt
ls -l _ex3.txt >> ex3.txt
