CC = gcc

src = $(wildcard  src/*.c)
CFLAGS = -Wall
CFLAGS += -I./include

bin = LIST1
$(bin) : $(src)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	-rm -rf $(bin)

.PHONY:clean
