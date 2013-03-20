#!/bin/bash

cat $HOME/.bash_history | awk '{print $1}' | sort | uniq -c | sort -nr | awk '{print $2 " - " $1}' | head
