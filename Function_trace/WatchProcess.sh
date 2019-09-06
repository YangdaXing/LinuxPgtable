#!/bin/bash
<<<<<<< HEAD
Times=10

while[ $Times -gt "0" ] 
    strace -c -ttt -o ans_$Times ./stream.o
    t
=======
Times=4

while [ $Times -gt 0 ] 
do
    strace -c -ttt -o ans_$Times ./stream.o
    ((Times--))
    echo $Times
done

exit
       
>>>>>>> 14f5c3f91c51d3e7ba0499b56df76dfa7506fe0b
