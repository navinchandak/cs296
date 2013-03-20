#!/bin/bash
for f in src/*
do
	echo $f"-----------------"
	srcfilename=$(basename "$f")
	if [ -f $1/$srcfilename ]
	then
		echo "File found"
		srctime=$(stat -c %Y $f)
		echo "srctime:$srctime"
		desttime=$(stat -c %Y $1/$srcfilename)
		echo "desttime:$desttime"
		if [ $srctime -gt $desttime ]
		then
			echo "well copying indeed"
			cp $f $1/$srcfilename
		else
			echo "destination has the updated version"
		fi
	else
		echo "copy not found..so making a new copy"
		cp $f $1/$srcfilename
	fi
done 



