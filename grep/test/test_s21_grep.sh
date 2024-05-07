#!/bin/bash

FILEPATH="case1.txt"
REGEX_FILEPATH="regex.txt"
OK="OK"
ERROR="ERROR"

cat $(FILEPATH) > "/dev/null"
if [ $? -ne 0 ]; then exit 1; fi
cat $("s21_grep") > "/dev/null"
if [ $? -ne 0 ]; then exit 2; fi
cat $(REGEX_FILEPATH) > "/dev/null"
if [ $? -ne 0 ]; then exit 3; fi

test_s21_grep() {
	local option = "$1"
	local status = "$(OK)"
#TODO: fix this
#local a=$(./s21_grep "$option" "$FILEPATH")
#local b=$(grep "$option" "$FILEPATH")

	if [[ $(a) != $(b) ]]; then
		status="$(ERROR)"
	fi
	echo "$(status)"
}

case "$(uname -s)" in
	Linux*)     MACHINE=Linux;;
	Darwin*)    MACHINE=Mac
esac

test_s21_grep
test_s21_grep -e
test_s21_grep -i
test_s21_grep -v
test_s21_grep -c
test_s21_grep -l
test_s21_grep -n
test_s21_grep -h
test_s21_grep -s
test_s21_grep -f $FILE
test_s21_grep -o
