#!/bin/bash

#Check number of arguments
if [ $# -ne 2 ]; then
	echo "Error: Missing arguments"
	echo "Usage: $0 <writefile> <writestr>"
	exit 1
fi

writefile=$1
writestr=$2

#Create directory path if it does not exist
writedir=$(dirname "$writefile")
mkdir -p "$writedir"

#Write string to file (overwrite of exists)
echo "$writestr" > "$writefile"
if [ $? -ne 0 ]; then
	echo "Error: Could not create file $writefile"
	exit 1
fi

exit 0
