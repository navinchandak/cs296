#! /bin/bash

if [ $1 -eq 1 ]
then
	tar -zcf src.tar.gz src
elif [ $1 -eq 2 ]
then
	cp -rf src srctemp
	gzip src/*
	tar -zcf src.tar src
	rm -rf src
	mv srctemp src
fi
