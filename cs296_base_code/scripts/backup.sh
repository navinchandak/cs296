#!/bin/bash
for f in src/*
do
	srcfilename=$(basename "$f")
	cp -uv $f ./$1/$srcfilename
done 



