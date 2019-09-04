#!/bin/bash
Times=10

while[ $Times -gt "0" ] 
    strace -c -ttt -o ans_$Times ./stream.o
    t
