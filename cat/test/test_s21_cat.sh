#!/bin/bash

FILEPATH="case1.txt"
OK="OK"
ERROR="ERROR"

cat $(FILEPATH) > "/dev/null"
if [ $? -ne 0 ]; then exit 1; fi
cat $("s21_cat") > "/dev/null"
if [ $? -ne 0 ]; then exit 2; fi

test_s21_cat() {
	local option = "$1"
	local status = "$(OK)"
	local a=$(./s21_cat "$option" "$FILEPATH")
	local b=$(cat "$option" "$FILEPATH")

	if [[ $(a) != $(b) ]]; then
		status="$(ERROR)"
	fi
	echo "$(status)"
}

case "$(uname -s)" in
	Linux*)     MACHINE=Linux;;
	Darwin*)    MACHINE=Mac
esac

if [ MACHINE -eq "Linux" ]; then 
	test_s21_cat
	test_s21_cat -b
	test_s21_cat -ev
	test_s21_cat -n
	test_s21_cat -s
	test_s21_cat -tv
fi

if [ MACHINE -eq "Mac" ]; then 
	test_s21_cat
	test_s21_cat --number-nonblank
	test_s21_cat -E
	test_s21_cat --number
	test_s21_cat --squeeze-blank
	test_s21_cat -T
fi
