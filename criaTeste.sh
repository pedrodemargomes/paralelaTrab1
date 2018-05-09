#!/bin/bash
FILE=grafoDeTeste.txt

if [ $# -lt 1 ]
then
	echo "Sem parametro do tamanho do grafo"
	exit -1
fi

echo $1 > $FILE 

for i in $(seq 1 $1)
do
	shuf -i 0-1000 -n $1 | tr '\n' ' ' >> $FILE
	echo '' >> $FILE
done


echo 0 >> $FILE 
