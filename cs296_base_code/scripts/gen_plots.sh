#!/bin/bash
./scripts/temp01.sh
for i in {1..6}
do
	gnuplot> load "./scripts/g05_plot0$i.gpt"
done
./scripts/temp02.sh
