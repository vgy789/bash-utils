CC=gcc
# не забудь включить флаги
CFLAGS=-Wall -Werror -Wextra -std=c11 -pedantic
OUTPUT_FILE=s21_cat

all: build

build: $(OUTPUT_FILE)

$(OUTPUT_FILE): 
	$(CC) -o $(OUTPUT_FILE) ../error.c s21_cat.c

clean:
	rm -rf *.o ./cat/ $(OUTPUT_FILE)

rebuild: clean all
