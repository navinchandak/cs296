#!/bin/bash

path=$1

ls -l $path | awk 'BEGIN{
	dirs = 0
	files = -1
}


{
	if ($1 ~ /^d/)
	{
		dirs = dirs + 1
	}
	else
	{
		files = files + 1
	}
}


END{
	printf "No. of files : %d \nNo. of directories : %d \n", files, dirs
}' 
echo "Name of all executable files within the given path are :"
find $path -executable -type f



