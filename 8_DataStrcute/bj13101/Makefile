CC = gcc
CFLAGS = -Wall -I include
VPATH = list

OBJS = main.o listlinkloop.o 
DEPEND = depend
TAGS = tags

all: main $(DEPEND) $(TAGS)

main: $(OBJS)

distclean: clean
	$(RM) main 
	$(RM) $(TAGS) 
	$(RM) $(DEPEND) 

$(DEPEND): $(OBJS:.o=.c)
	$(CC) -I include -MM $^ > $(DEPEND)

-include $(DEPEND)

$(TAGS): $(OBJS:.o=.c)
	ctags $^ include/*.h 

clean:
	$(RM) *.o

.PHONY:clean
