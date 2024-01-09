objects = find ls tree

all: $(objects)

$(objects): %: %.c
	gcc -Wall -Werror -fsanitize=address -Wvla $^ -o $@

clean:
	rm -rf $(objects)
