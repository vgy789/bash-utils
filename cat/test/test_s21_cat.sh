#!/bin/bash

OK_MSG="OK"
ERROR_MSG="ERROR"
PROGRAM_PATH="../s21_cat"

if [ ! -f "$PROGRAM_PATH" ]; then 
	echo "no such file $PROGRAM_PATH"
	exit 1
fi

test_s21_cat() {
	local option="$1"
	local file="$2"
	local status="$OK_MSG"
	local cat_output="a_output.txt"
    local s21_cat_output="b_output.txt"

	"$PROGRAM_PATH" "$option" "$file" "$file" > "$cat_output"
    cat "$option" "$file" "$file" > "$s21_cat_output"

	if ! diff -q "$cat_output" "$s21_cat_output" > /dev/null; then
		status="$ERROR_MSG"
	else
		status="$OK_MSG"
	fi

	rm "$cat_output" "$s21_cat_output"

	if [ "$status" == "$OK_MSG" ]; then
		echo -e "$status" "$option"
	else
		echo -e "$status" "$option"
	fi
}

case "$(uname -s)" in
	Linux*)     MACHINE=Linux;;
	Darwin*)    MACHINE=Mac
esac

for file in test*; do
	echo "[$file]"
	cat $file > "/dev/null" || continue
	
	test_s21_cat -b $file
	test_s21_cat -v $file
	test_s21_cat -e $file
	test_s21_cat -n $file
	test_s21_cat -s $file
	test_s21_cat -t $file
	test_s21_cat -bn $file
	test_s21_cat -nb $file
	test_s21_cat -te $file
	test_s21_cat -bs $file

	if [[ $MACHINE == "Linux" ]]; then 
		test_s21_cat --number-nonblank $file
		test_s21_cat -T $file
		test_s21_cat -E $file
		test_s21_cat -TE $file
	fi
done
