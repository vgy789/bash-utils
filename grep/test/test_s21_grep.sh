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

#	"$PROGRAM_PATH" "$option" "$file" "$file" > "$grep_output"
#    grep "$option" "$file" "$file" > "$s21_grep_output"

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

#	test_s21_grep -b $file
#	test_s21_grep -v $file
#	test_s21_grep -e $file
#	test_s21_grep -n $file
#	test_s21_grep -s $file
#	test_s21_grep -t $file
#	test_s21_grep -bn $file
#	test_s21_grep -nb $file
#	test_s21_grep -te $file
#	test_s21_grep -bs $file
done
