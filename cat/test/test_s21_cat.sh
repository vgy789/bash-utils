#!/bin/bash

OK_MSG="OK"
ERROR_MSG="ERROR"

cat "../s21_cat" > "/dev/null" ||  exit 1


test_s21_cat() {
	local option="$1"
	local file="$2"
	local status="$OK_MSG"
	local cat_output="a_output.txt"
    local s21_cat_output="b_output.txt"

	"../s21_cat" "$option" "$file" > "$cat_output"
    cat "$option" "$file" > "$s21_cat_output"

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
		test_s21_cat --number-nonblank -E $file
		test_s21_cat --number $file
		test_s21_cat --squeeze-blank $file
		test_s21_cat -T $file
		test_s21_cat -TE --number-nonblank --squeeze-blank --number $file
	fi
	echo
done