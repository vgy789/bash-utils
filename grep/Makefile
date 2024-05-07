CC=gcc
FLAGS=-Werror -Wextra -std=c11 -pedantic
#FLAGS=-Wall -Werror -Wextra -std=c11 -pedantic
OUTPUT_FILE=s21_grep

all: build

build: $(OUTPUT_FILE)

$(OUTPUT_FILE): cat_utility.o error.o
	$(CC) $(CFLAGS) -o $(OUTPUT_FILE) s21_cat.c $^

cat_utility.o:
	$(CC) $(CFLAGS) -c cat_utility.c

error.o:
	$(CC) $(CFLAGS) -c ../common/error.c

clean:
	rm -rf *.o $(OUTPUT_FILE)

rebuild: clean all
