#!/bin/sh
#finder script to search the content from a directory

# 1. Check the number of arguments, it should equals to 2
if [ $# -ne 2 ]; then
    echo "Error: Two arguments required."
    echo "Usage: $0 <filesdir> <searchstr>"
    exit 1
fi

# 2. Collect input arguments and assign to variables
filesdir=$1
searchstr=$2

# 3. Validate the directory
if [ ! -d "$filesdir" ]; then
    echo "Error: '$filesdir' is not a valid directory."
    exit 1
fi

# 4. Count number of files in the directory
# find all files recusively and pass to wc to count humber of lines
num_files=$(find "$filesdir" -type f | wc -l)

# 5. Count the number of matching lines
# find all matched $searchstr from $filesdir, do not throw any error, and count the matched string, assign result to num_matchs
num_matchs=$(grep -r "$searchstr" "$filesdir" 2>/dev/null | wc -l)

echo "The number of files are $num_files and the number of matching lines are $num_matchs"

exit 0