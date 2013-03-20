#/bin/bash
filename=./data/lab05_g05_data.csv
printf "" > $filename
for j in {1..100}
do
	for i in {1..100}
	do
		printf "$j, $i, " >> $filename
		awk '/ms/ { printf("%f, ",($(NF-1)))}' ./data/out-$i-$j.txt | sed 's/..$//' >> $filename
		echo >> $filename
	done
done
