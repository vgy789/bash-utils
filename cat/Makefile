CC=gcc
CFLAGS=
#-Werror -Wextra -std=c11 -pedantic
OUTPUT_FILE=s21_cat

all: build

build: $(OUTPUT_FILE)

$(OUTPUT_FILE): options_process.o platform.o error.o
	$(CC) $(CFLAGS) -o $(OUTPUT_FILE) s21_cat.c $^

options_process: process.o platform.o
	$(CC) $(CFLAGS) -c options_process.c

platform.o: error.o
	$(CC) $(CFLAGS) -c platform.c

error.o:
	$(CC) $(CFLAGS) -c error.c

clean:
	rm -rf *.o $(OUTPUT_FILE)

rebuild: clean all
