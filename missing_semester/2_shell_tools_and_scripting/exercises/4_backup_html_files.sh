#!/usr/bin/env sh

# Description: 
# Your task is to write a command that recursively finds all HTML files in the folder and makes a zip with them. Note that your command should work even if the files have spaces (hint: check -d flag for xargs).


find_path=$1
zip_name=./final

if [ $# -lt 1 ]; then
	echo "Usage: $0 path [zip_name]"
	exit 1
elif [ $# -eq 2 ]; then
	zip_name=$2
fi


find_and_zip_html_files() {
	find $1 -type f -name *.html -print0 | xargs --null tar czf $zip_name.zip
}

find_and_zip_html_files $find_path
