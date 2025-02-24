all: WordSearchGenerator

WordSearchGenerator: WordSearchGenerator.c
	gcc WordSearchGenerator.c -Wall -Werror -o WordSearchGenerator

clean:
	rm -rf WordSearchGenerator