#! /bin/bash
# ﻿Гусаров Аркадий РК6-13Б 1 курс. Программа для перечисления всех одинаковых чисел различных месяцев любого указанного или текущего года, которые выпадают на заданный день недели.

if [ $# -eq 01 ]                # если 1 переменная 
then
    input_year=`date +"%Y"`
    dow=$1
    
elif [ $# -eq 02 ]              # если 2 переменные
then
    input_year=$1
    dow=$2
else                            # переменных больше 2-х или меньше 1
    exit 133;
fi

if [ $input_year -le 0 ]        # год > 0
then
    exit 134;
fi

#case $dow in
#    Пн) Mon;;
#    Вт) Tue;;
#    Ср) Wed;;
#    Чт) Thu;;
#    Пт) Fri;;
#    Сб) Sat;;
#    Вс) Sun;;
#    *) break;;
#esac

count=1

date_base=`date -d "01/01/$input_year" +"%x"`           # "%x" - формат вывода даты dd.mm.yyyy

day=`date -d "01/01/$input_year" +"%a"`                 # "%a" - день недели

while [ $day != $dow ]
do
    date_base=`date -d "01/01/$input_year $count Day" +"%x"`

    day=`date -d "01/01/$input_year $count Day" +"%a"`
    
    let ++count
done

set ${date_base//./' '}

dd=$1
mm=$2
yy=$3

date_base=$mm/$dd/$yy

date_=`date -d "$date_base 1 Week" '+%m/%d/%Y'`
date_base=`date -d "$date_base" '+%m/%d/%Y'`

#echo "date_base = "$date_base
#echo "date_ = "$date_

let ny=$yy+1

while [ ${yy} -ne ${ny} ]
do    
    # игнорируем февраль
    if [ `date -d "$date_base" +"%m"` -eq 02 ]
    then
        date_base=`date -d "$date_base 1 Month" '+%m/%d/%Y'`
        date_=`date -d "$date_base 1 Week" '+%m/%d/%Y'`
    fi
    
    a=`date -d "$date_base" +"%d"`
    b=`date -d "$date_" +"%d"`

    if [ ${a} -eq ${b} ]
    then
        c=`date -d "$date_" '+%m/%d/%Y'`
        echo $c
    
        date_base=`date -d "$date_base 1 Week" '+%m/%d/%Y'`
        date_=`date -d "$date_base 1 Week" '+%m/%d/%Y'`
    else
        
        date_=`date -d "$date_ 1 Week" '+%m/%d/%Y'`               # переход на неделю
        
        # ограничить переход в следующий год
        year=`date -d "$date_" +"%Y"`
        if [ $year -ne $yy ]
        then
            date_base=`date -d "$date_base 1 Week" '+%m/%d/%Y'`
            date_=`date -d "$date_base 1 Week" '+%m/%d/%Y'`
        fi
    fi
    
    yy=`date -d "$date_base" +"%Y"`
done
