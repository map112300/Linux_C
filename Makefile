all : grep

grep : grep.c 
	gcc -g -Wall -Werror -Wvla -fsanitize=address grep.c -o grep

clean : 
	rm -rf grep 