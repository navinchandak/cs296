#!/bin/bash

#Replacing Fitzwilliam by Hardik, Darcy by Navin and Elizabeth by Preetham 

sed s/\`\`/\"/g <./data/pnp_austen.txt | sed s/\'\'/\"/g | sed 's/\<Fitzwilliam\>/Hardik/g' | sed 's/\<Darcy\>/Navin/g' | sed 's/\<Elizabeth\>/Preetham/g' >./data/pnp_austen_cs296.txt
