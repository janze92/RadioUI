#!/bin/bash

POLKU=/tmp/todoxmms.txt

### Set initial time of file
LTIME=`stat -c %Z $POLKU`

while true    
do
   ATIME=`stat -c %Z $POLKU`

   if [[ "$ATIME" != "$LTIME" ]]
   then    

	tapahtuma=$(cat $POLKU)
	    echo "$tapahtuma"

	if [ "$tapahtuma" == "play" ]; then
		xmms2 play
		
	elif [ "$tapahtuma" == "stop" ]; then
		xmms2 stop
		
    elif [ "$tapahtuma" == "next" ]; then
        xmms2 next
        
	elif [ "$tapahtuma" == "pause" ]; then
		xmms2 pause
		
	elif [ "$tapahtuma" == "prev" ]; then
		xmms2 prev
		
	elif [ "$tapahtuma" == "toggleplay" ]; then
		xmms2 toggleplay
		
	elif [ "$tapahtuma" == "suffle" ]; then
		xmms2 suffle
		
	elif [ "$tapahtuma" == "seek +15" ]; then
		xmms2 seek +15

	elif [ "$tapahtuma" == "break" ]; then
		break;

	elif [ "$tapahtuma" == "seek -15" ]; then
		xmms2 seek -15


	fi
       LTIME=$ATIME
   fi
   sleep 0.3
done
