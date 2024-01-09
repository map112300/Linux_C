objects = find ls tree uniq sort greo

all: $(objects)

$(objects): %: %.c
	gcc -Wall -Werror -fsanitize=address -Wvla $^ -o $@

clean:
	rm -rf $(objects)
