CC = gcc
CFLAGS = -Wall -Werror -Wextra
PTH = ../build/
EXEC = Alias
CFILES = data.c file_search.c
MAIN = alias.c
OBJECTS = $(CFILES:.c=.o)
HEADERS = $(CFILES:.c=.h)

all: build clean

build: $(EXEC)

$(EXEC): $(OBJECTS) $(MAIN)
	$(CC) $(CFLAGS) $^ -o $(PTH)$(EXEC)

$(OBJECTS): $(CFILES)
	$(CC) $(CFLAGS) -c $^

clean:
	rm -rf $(CFILES:.c=.o) $(CFILES:.c=.gch) $(CFILES:.c=.a)

clean_exe:
	rm -rf ../build/[!.gitkeep]*

force_clean: clean clean_exe