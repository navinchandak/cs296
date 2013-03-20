#!/bin/bash

destname="./data/lab05_g05_data_temp.csv"
srcname="./data/lab05_g05_data.csv"
printf "" > $destname
awk -F ',' '{if ($2==" 29") {print}}' $srcname > $destname
