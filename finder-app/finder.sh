#!/bin/bash

# Check the number of arguments
if [ $# -ne 2 ]; then
	echo "Error: Missing arguments"
	echo "Usage: $0 <filesdir> <searchstr>"
	exit 1
fi

filesdir=$1
searchstr=$2

# Check of filesdir exists and is a directort
if [ ! -d "$filesdir" ]; then
	echo "Error: $filesdir is not a valid directory"
	exit 1
fi

#Count number of files (recursively)
num_files=$(find "$filesdir" -type f | wc -l)

#Count number of matching lines containing searchstr
num_matches=$(grep -R "$searchstr" "$filesdir" 2>/dev/null | wc -l)

#Print result
echo " The number of files are $num_files and the number of matching lines are $num_matches"

exit 0
