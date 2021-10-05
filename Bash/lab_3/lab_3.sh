#! /bin/bash
# ﻿Гусаров Аркадий РК6-13Б 1 курс. Программа подсчета числа палиндромов в любой заданной последовательности символьных слов без учета регистра букв. 

count=0

for i in $*
do
	check=`expr "$i" : '.*[0-9]'`			

	if let $check==0
	then
		word=$i
		word=`tr A-Z a-z <<< $word`

		if [[ $(rev <<< "$word") == "$word" ]]
		then
			let count++
		fi
	fi
done

echo $count
