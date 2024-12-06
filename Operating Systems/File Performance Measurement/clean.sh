# Removes all the copy files
#!/bin/bash

# Check if there are files matching the pattern
files=$(ls *copy* 2>/dev/null)

if [ -z "$files" ]; then
    echo "No files containing the word 'copy' were found."
    exit 0
fi

# Remove the files containing "copy" in their name
rm -f *copy*

# Confirm removal
echo "All files containing the word 'copy' have been removed."

