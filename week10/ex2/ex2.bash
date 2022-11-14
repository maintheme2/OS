#!/bin/bash

mkdir week01/
touch week01/file.txt
echo "some content" >> week01/file.txt
ln week01/file.txt _ex2.txt
INUM=$(ls -i _ex2.txt | cut -d ' ' -f1)
find . -inum $INUM >> ex2.txt
find . -inum $INUM ! -name "file.txt" -exec rm {} \; >> ex2.txt
cat ex2.txt
