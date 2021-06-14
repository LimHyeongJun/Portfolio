#!/bin/bash

declare -i red=0
declare -i green=-1
declare -i choose=0
declare -i up_down=0
back="B "
fore="F "

function getCmds() {
	ps -ef > temp
	grep ^$1 temp > ps_result
	rm ./temp
	IFS_backup="$IFS"
	IFS=$'\n'
	Tty=($(cat ps_result | sort -k2 -g -r | awk '{print $6}'))
	Cmds=($(cat ps_result | sort -k2 -g -r | cut -c 51-))
	PIDs=($(cat ps_result | sort -k2 -g -r | awk '{print $2}'))
	STimes=($(cat ps_result | sort -k2 -g -r | awk '{print $5}'))
	
	IFS="$IFS_backup"
}

function add_Back() {
	if [[ -n $1 ]]; then
		n="$back""$1"
	elif [[ -z $1 ]]; then
		n="$1"
	fi
}

function add_Fore() {
	if [[ -n $1 ]]; then
		n="$fore""$1"
	else
		n="$1"
	fi
}

highlight() {
	if [ $2 = $1 ]; then
		echo -n [$3m
	fi
}

while [ 1 ]
do
clear

echo ""
echo '______                      _    _'
echo '| ___ \                    | |  (_)'
echo '| |_/ /  _ __   __ _   ___ | |_  _   ___   ___'
echo '|  __/  |  __| / _  | / __|| __|| | / __| / _ \'
echo '| |     | |   | (_| || (__ | |_ | || (__ |  __/'
echo '\_|     |_|    \__,_| \___| \__||_| \___| \___|'
echo ''
echo '(_)       | |    (_)'
echo ' _  _ __  | |     _  _ __   _   _ __  __'
echo '| ||  _ \ | |    | ||  _ \ | | | |\ \/ /'
echo '| || | | || |____| || | | || |_| | >  <'
echo '|_||_| |_|\_____/|_||_| |_| \__,_|/_/\_\'

if [[ $red -lt 0 ]]; then
	red=0; fi

if [[ $choose -lt 0 ]]; then
	choose=0 
elif [[ $choose -eq 2 ]]; then
	choose=1; fi

if [[ $up_down -lt 0 ]]; then
	up_down=0; fi

#User_Name=($(ps -ef | cut -f 1 -d " " | sed "1d" | sort | uniq ))
#getCmds ${User_Name[$red]}

#declare -i num_of_Username="${#User_Name[*]}"
#declare -i num_of_Cmds="${#Cmds[*]}"
#
#if [[ $red -eq $num_of_Username ]]; then
#	red=`expr $num_of_Username - 1`; fi
#
#if [[ $green -eq $num_of_Cmds ]]; then
#	green=`expr $green - 1`; fi


#-----------------------------------------------------------출력줄---------------------------------------------------------------

echo "-NAME-----------------CMD--------------------PID-----STIME-----"

if [[ $red -eq $num_of_Username ]]; then
	red=`expr $num_of_Username - 1`; fi

if [[ $green -eq $num_of_Cmds ]]; then
	green=`expr $green - 1`; fi

User_Name=($(ps -ef | cut -f 1 -d " " | sed "1d" | sort | uniq ))
getCmds ${User_Name[$red]}

declare -i num_of_Username="${#User_Name[*]}"
declare -i num_of_Cmds="${#Cmds[*]}"

if [[ $up_down -eq `expr $num_of_Cmds - 19` ]]; then
	up_down=`expr $up_down - 1`; fi


if [ "$up_down" -eq 0 ]; then
	for(( i=0; i<20; i++ )); do
	if [ "${Tty[$i]}" = '?' ]; then
		add_Back ${Cmds[$i]}
	else
		add_Fore ${Cmds[$i]}
	fi

	echo -n "|"
		highlight $i $red 41
		printf "%20s" ${User_Name[$i]}
		echo -n [0m
	echo -n "|"
		IFS_backup="$IFS"
		IFS=$'\n'
	highlight $i $green 42
		printf "%-22.22s|%7s|%9s" ${n} ${PIDs[$i]} ${STimes[$i]}
	echo -n [0m
	echo -n "|"
		IFS="$IFS_backup"
		printf "\n"
	done

elif [ "$up_down" -gt 0 ]; then
	for (( i=0; i<20; i++ )); do
	k=`expr $i + $up_down`
	if [ "${Tty[$k]}" = '?' ]; then
		add_Back ${Cmds[$k]}
	else
		add_Fore ${Cmds[$k]}
	fi

	echo -n "|"
		highlight $i $red 41
		printf "%20s" ${User_Name[$i]}
		echo -n [0m
	echo -n "|"
		IFS_backup="$IFS"
		IFS=$'\n'
	highlight $k $green 42
		printf "%-22.22s|%7s|%9s" ${n} ${PIDs[$k]} ${STimes[$k]}
	echo -n [0m
	echo -n "|"
		IFS="$IFS_backup"
		printf "\n"
	done
fi

echo "---------------------------------------------------------------"

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
			elif [[ $choose -eq 1 ]] && [[ $green -gt 0 ]] && [[ $green -gt $up_down ]]; then
				green=`expr $green - 1`; continue
			elif [[ $choose -eq 1 ]] && [[ $up_down -gt 0 ]] && [[ $green -eq $up_down ]]; then
				up_down=`expr $up_down - 1`; green=`expr $green - 1`; continue
			fi
		elif [[ ${y}${z} == "[B" ]]; then
			if [[ $choose -eq 0 ]]; then
				red=`expr $red + 1`; continue
			elif [[ $choose -eq 1 ]] && [[ $green -lt `expr $up_down + 19` ]]; then
				green=`expr $green + 1`; continue
			elif [[ $choose -eq 1 ]] && [[ $green -eq `expr $up_down + 19` ]]; then
				up_down=`expr $up_down + 1`; green=`expr $green + 1`; continue
			fi
		elif [[ ${y}${z} == "[C" ]]; then
			if [[ $choose -eq 0 ]]; then
				choose=`expr $choose + 1`; green=0; continue
			fi
		elif [[ ${y}${z} == "[D" ]]; then
			choose=`expr $choose - 1`; green=-1; up_down=0; continue
       		fi
	else
		continue
	fi
done
