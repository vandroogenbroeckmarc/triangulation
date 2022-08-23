CC = gcc -std=c99

CFLAGS = -O3 -D _GNU_SOURCE -D _XOPEN_SOURCE=500 -Wall -Wpointer-arith -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations
LDFLAGS = $(CFLAGS) -lm -lrt

EXEC = triangulation
MAKEFILE = Makefile

SRC = $(wildcard *.c)
INC = $(wildcard *.h)
OBJ = $(patsubst %.c,%.o,$(SRC))
DEP = $(patsubst %.c,%.d,$(SRC))

all: $(EXEC)

.PHONY: stats clean

$(EXEC): $(OBJ)
	@printf "Linking $@ ... \r\n"
	@$(CC) $(OBJ) $(LDFLAGS) -o $@

-include $(DEP)

%.o: %.c $(MAKEFILE)
	@printf "Compiling $@ ... \r\n"
	@$(CC) -c $(CFLAGS) $< -o $@
	@$(CC) -MM $(CFLAGS) -MT $*.o $< > $*.d


#File list for tarball and stats
FILES_LIST = $(wildcard $(MAKEFILE) *.c *.h)

# display some statistics on source files
stats:
	@echo lines words bytes file
	@ls $(FILES_LIST) | xargs wc

# cleaners
clean:
	rm -f $(OBJ) $(DEP)

mrproper: clean
	rm -f $(EXEC)
	rm -f *.pgm
	rm -f *.ppm
	rm -f *~
	
doc: 
	doxygen doc/triangulation.doxygen
