#!/bin/bash

declare -i red=0
declare -i green=0
declare -i choose=0

while [ 1 ]
do

echo "______                      _    _"
echo "| ___ \                    | |  (_)"
echo "| |_/ /  _ __   __ _   ___ | |_  _   ___   ___"
echo "|  __/  |  __| / _  | / __|| __|| | / __| / _ \\"
echo "| |     | |   | (_| || (__ | |_ | || (__ |  __/"
echo "\_|     |_|    \__,_| \___| \__||_| \___| \___|"
echo ""
echo "(_)       | |    (_)"
echo " _  _ __  | |     _  _ __   _   _ __  __"
echo "| ||  _ \ | |    | ||  _ \ | | | |\ \/ /"
echo "| || | | || |____| || | | || |_| | >  <"
echo "|_||_| |_|\_____/|_||_| |_| \__,_|/_/\_\\"

echo "-NAME-----------------CMD------------------PID----STIME----"

if [[ $red -lt 0 ]]; then
	red=0; fi

if [[ $green -lt 0 ]]; then
	green=0; fi

if [[ $choose -lt 0 ]]; then
	choose=0 
elif [[ $choose -eq 2 ]]; then
	choose=1; fi

IFS=$'\n' Other_User_Name=(`ps -ef | grep -v '?' | awk '{print $1}' | sort -f | uniq | grep -v 'UID'`)
User_Name=($(ps -ef | sort -f | grep -v '?' | awk '{printf("%20s\n", $1)}' | grep -v 'UID' | uniq))

if [[ $red -eq "${#User_Name[@]}" ]]; then
	red=`expr ${#User_Name[@]} - 1`; fi

arr=($(ps -ef | sort | grep -v '?' | grep "${Other_User_Name[$red]}" | awk '{printf("%-20s|%6s|%8s\n", $8, $2, $5)}'))

declare -i arr_length="${#arr[*]}"

if [[ $green -eq "${#arr[*]}" ]]; then
	green=`expr $arr_length - 1`; fi


#--------------CMD, PID, STIME 묶어놓은 배열 인덱스가 비어있는 거면 밑에껄로 채우기
for(( a=0; a<20; a++ )); do
	if [[ -z ${arr[$a]} ]]; then
		arr[$a]="                    |      |        "; fi
done

#------------------USERNAME 배열 인덱스가 비어있으면 20칸짜리 빈칸으로 만들기

for(( b=0; b<20; b++ )); do
	if [[ -z ${User_Name[$b]} ]]; then
		User_Name[$b]="                    "; fi
done

#-----------------------------------------------------------출력줄---------------------------------------------------------------

for(( i=0; i<20; i++ )); do
	echo -n "|"

	if [[ $red == "$i" ]] ; then
		echo -n [41m${User_Name[$red]}
	else
		echo -n ${User_Name[$i]}; fi

	echo -n [0m"|"

	if [[ $choose -eq 1 ]] && [[ $green == "$i" ]]; then
		echo -n [42m${arr[$i]}
	else
		echo -n ${arr[$i]}; fi

	echo [0m"|"
done

echo "-----------------------------------------------------------"

echo "If you want to exit , Please Type 'q' or 'Q'"
read -t3 -s -n1 x
	if [[ ${x} = "q" ]] || [[ ${x} = "Q" ]]; then
      	 	break
	elif [[ -z ${x} ]]; then
		continue
	elif [[ ${x} = "" ]]; then
		read -s -n2 y z
		if [[ ${y}${z} == "[A" ]]; then
			if [[ $choose -eq 0 ]]; then
				red=`expr $red - 1`; continue
			else
				green=`expr $green - 1`; continue
			fi
		elif [[ ${y}${z} == "[B" ]]; then
			if [[ $choose -eq 0 ]]; then
				red=`expr $red + 1`; continue
			else
				green=`expr $green + 1`; continue
			fi
		elif [[ ${y}${z} == "[C" ]]; then
			choose=`expr $choose + 1`; continue
		elif [[ ${y}${z} == "[D" ]]; then
			choose=`expr $choose - 1`; green=0; continue
       		fi
	else
		continue
	fi
done
