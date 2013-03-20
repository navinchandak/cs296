#!/bin/bash
isRunning=$(ps -ef | grep firefox | awk '{if ($8 == "/usr/lib/firefox/firefox")  print $2,$1; }')
if [ -z "$isRunning" ]
then
	echo "Firefox is not running"
else
	user=$(whoami)
	echo $isRunning
	result=$(echo "$isRunning"| awk '{if ($2 =="'$user'") print; }')
	firefoxuser=$(echo "$result" | awk '{print $2}')
	if [ $user == $firefoxuser ]
	then
		pid=$(echo "$result" | awk '{print $1}' | head -n1)
		echo "Should I kill firefox? (\"y\"/\"Y\")"
		read yn
		if [ $yn == "y" ]
		then
			kill -9 $pid
		elif [ $yn == "Y" ]
		then 
			kill -9 $pid
		fi
	else
		echo "The current user does not have permission to terminate the process"
	fi
	
fi



