grep hello data1.txt
grep goodbye data1.txt
grep hello data1.txt data2.txt data3.txt
grep -e hello -e a -e b data1.txt
grep -e hello -e a -e b data1.txt data2.txt data3.txt
grep -f patterns1.txt data1.txt
grep -f patterns1.txt data2.txt
grep -f patterns1.txt -f patterns2.txt data3.txt


#!/bin/bash

OK_MSG="OK"
ERROR_MSG="ERROR"
PROGRAM_PATH="../s21_cat"

if [ ! -f "$PROGRAM_PATH" ]; then 
	echo "no such file $PROGRAM_PATH"
	exit 1
fi

test_s21_grep() {
	local option="$1"
	local file="$2"
	local status="$OK_MSG"
	local grep_output="a_output.txt"
    local s21_grep_output="b_output.txt"

	"$PROGRAM_PATH" "$option" "$file" "$file" > "$grep_output"
    grep "$option" "$file" "$file" > "$s21_grep_output"

	if ! diff -q "$grep_output" "$s21_grep_output" > /dev/null; then
		status="$ERROR_MSG"
	else
		status="$OK_MSG"
	fi

	rm "$grep_output" "$s21_grep_output"

	if [ "$status" == "$OK_MSG" ]; then
		echo -e "$status" "$option"
	else
		echo -e "$status" "$option"
	fi
}

for file in test*; do
	echo "[$file]"
	grep $file > "/dev/null" || continue

	test_s21_grep -b
	test_s21_grep -v
	test_s21_grep -e
	test_s21_grep -n
	test_s21_grep -s
	test_s21_grep -t
	test_s21_grep -bn
	test_s21_grep -nb
	test_s21_grep -te
	test_s21_grep -bs
done
