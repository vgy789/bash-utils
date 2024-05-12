#!/bin/bash

OK_MSG="OK"
ERROR_MSG="ERROR"
PROGRAM_PATH="./s21_grep"
status="$OK_MSG"
TEST_DIR=$1

if [ ! -f "$PROGRAM_PATH" ]; then 
	echo "no such file $PROGRAM_PATH"
	exit 1
fi

test_s21_grep() {
	local option="$1"
	local file="$2"
	local grep_output="grep_output.txt"
    local s21_grep_output="s21_grep_output.txt"

	"$PROGRAM_PATH" "$option" "$file" "$file" > "$grep_output"
    grep "$option" "$file" "$file" > "$s21_grep_output"

	if ! diff -q "$grep_output" "$s21_grep_output" > /dev/null; then
		status="$ERROR_MSG"
	else
		status="$OK_MSG"
	fi

	rm "$grep_output" "$s21_grep_output"

	if [ "$status" == "$OK_MSG" ]; then
        ((successful_tests++))
    else
        ((failed_tests++))
    fi
	echo -e "$status" "$option"
}

for file in test*; do
	echo "[$file]"
	cat $file > "/dev/null" || continue
done

grep hello data1.txt
grep goodbye data1.txt
grep hello data1.txt data2.txt data3.txt
grep -e hello -e a -e b data1.txt
grep -e hello -e a -e b data1.txt data2.txt data3.txt
grep -f patterns1.txt data1.txt
grep -f patterns1.txt data2.txt
grep -f patterns1.txt -f patterns2.txt data3.txt
