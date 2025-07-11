#!/bin/sh
#writer script to search the content from a directory

# 1. Check if the input arguments are valid
if [ $# -ne 2 ]; then
    echo "Error: Two arguments required."
    echo "Usage: $0 <writefile> <writestr>"
    exit 1
fi

# 2. Assign the input arguments to variables
writefile=$1
writestr=$2

# 3. extract the directory from the input file path
dirpath=$(dirname "$writefile")

# 4. Create the directory if not exist
mkdir -p "$dirpath"

# verification
if [ $? -ne 0 ]; then
    echo "Error: Failed to create directory '$dirpath'"
    exit 1
fi

# 5. Write the content to file
echo "$writestr" > "$writefile"

if [ $? -ne 0 ]; then
    echo "Error: Could not write to file '$writefile'"
    exit 1
fi
# 6. Exit successfull
exit 0