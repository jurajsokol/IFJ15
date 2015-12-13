CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -g -MMD -MP
# vytvori zoznsm .o suborov
OBJECTS = $(patsubst %.c,%.o,$(wildcard *.c))
BIN = project

project: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BIN)

%.o: %.c
	$(CC) -c $(CFLAGS) $*.c

-include $(OBJECTS:%.o=%.d)

clean:
	rm -f *.o *.d $(BIN)

# zamže .o súbory
clean_o:
	rm -f *.o

# zmaže závislosti
clean_d:
	rm -f *.d

# zmaže .cc súbory
clean_cc:
	rm -f *.cc
