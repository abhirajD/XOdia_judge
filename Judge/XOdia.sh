#!/bin/bash

cd /home/umang/Desktop/xodia/submissions

for i in {1..2}
do
	if [ $i -eq 1 ] || [ $i -eq 8 ] || [ $i -eq 9 ]
	then
		x=$i.c
	else
		x=$i.cpp
	fi
	for j in {1..14}
	do
		if [ $i -ne $j ]
		then
			if [ $j -eq 1 ] || [ $j -eq 8 ] || [ $j -eq 9 ]
			then
				o=$j.c
			else
				o=$j.cpp
			fi
			python Judge.py $x $o
		fi
		j=$(($j+1))
	done
	i=$(($i+1))
done
