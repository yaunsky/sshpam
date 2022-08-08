CFLAGS += -Werror -Wall
example.so: example.c
	gcc $(CFLAGS) -fPIC -shared -Xlinker -x -o $@ $<
