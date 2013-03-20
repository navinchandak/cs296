#/bin/bash
for i in {1..100}
do
	for j in {1..100}
	do
		./mybins/cs296_exe_05 $i > ./data/out-$i-$j.txt 
	done
done

