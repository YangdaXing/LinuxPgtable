#!/bin/bash
Times=4

while [ $Times -gt 0 ] 
do
    strace -c -ttt -o ans_$Times ./stream.o
    ((Times--))
    echo $Times
done

exit
       
