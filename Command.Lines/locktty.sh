#!/bin/sh
# Tuan Nguyen
# Project 4
# COMP 322L - Class #16766 (MoWe 12:30PM-01:45PM)
# * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# Modify the above locktty script so that the new user has only 3 attempts
# to reinstate the session, and furthermore, it has to be done within 15 minutes
# * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
trap ‘‘ 1  2  3  18
stty   -echo
# Set time limit to 15 minutes
TIMELIMIT=90                                          
echo Enter key:
read key_1
echo
echo Again:
read key_2
echo
# User password setup succeeds
if [ "$key_1" == "$key_2" ]
then
    tput clear
	try=1
	echo Enter password:
    read key_3

    while [ "$key_3" != "$key_2" ]
    do
        case "$try" in 
        # Start timing on the first try
        1)  start=$(date +%s)                           
            timepass=`expr $TIMELIMIT + 1`
            ;;
        2)  timepass=`expr $TIMELIMIT + 1`              
            ;;
        # Calculate elapsing time to the 3rd try
        3)  end=$(date +%s)
            timepass=$((end - start))                   
            ;;
        # Other try won't pass the test below, leading to 15-minute sleep
        *)  timepass=$TIMELIMIT                         
            ;;                                          
        esac
        # Test elapsing time since the first try must be > 15 minutes
        if [ "$timepass" -gt "$TIMELIMIT" ]		        
		then		                   
			try=`expr $try + 1`
		else
			echo Please wait, too many tries in a short time period! z..z...z..
            # Reset number of try to for a new session
			try=1
            # Sleep for 15 minutes then wake up for a new session					            
			sleep $TIMELIMIT                            
		fi

        echo Enter password:
        read key_3
	done

    echo tty is now unlocked
    tput clear
    stty echo
    exit 0
fi
# User password setup fails
if  [ "$key_1" != "$key_2" ]
then
     echo locktty: Keys do not match! ...Try again
     stty echo
     exit 1
fi