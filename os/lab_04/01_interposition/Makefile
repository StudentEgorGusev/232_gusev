CC=gcc
CFLAGS=-Wall -Wextra -std=c2x
PIC=-fPIC
LIBS=-lm

STATIC=libstat.a
SHARED=libdyn.so
PRELOAD=preload.so
TARGET=solution

SRC_STAT=fred.c john.c
SRC_DYN=bill.c sam.c

all: $(TARGET) $(PRELOAD)

$(STATIC): $(SRC_STAT:.c=.o)
	ar cr $@ $^

%.o: %.c lib.h
	$(CC) $(CFLAGS) -c $< -o $@

%.pic.o: %.c lib.h
	$(CC) $(CFLAGS) $(PIC) -c $< -o $@

$(SHARED): $(SRC_DYN:.c=.pic.o)
	$(CC) $(CFLAGS) -shared -o $@ $^ $(LIBS)

preload_interpose.c:
	@printf '#define _GNU_SOURCE\n#include <dlfcn.h>\n#include "lib.h"\nvoid bill(char*s){void(*o)(char*)=dlsym(RTLD_NEXT,"bill");o(s);}void sam(double x){void(*o)(double)=dlsym(RTLD_NEXT,"sam");o(x);}\n' > $@

$(PRELOAD): preload_interpose.c lib.h
	$(CC) $(CFLAGS) $(PIC) -shared preload_interpose.c $(LIBS) -o $@

solution.o: solution.c lib.h
	$(CC) $(CFLAGS) -c solution.c -o $@

$(TARGET): solution.o $(STATIC) $(SHARED)
	$(CC) $(CFLAGS) solution.o -L. -lstat -ldyn $(LIBS) -Wl,-rpath,'$$ORIGIN' -o $@

run: all
	LD_PRELOAD=$(PRELOAD) ./$(TARGET)

test: all
	python3 -m unittest discover -v tests

clean:
	rm -f *.o *.pic.o $(STATIC) $(SHARED) $(PRELOAD) preload_interpose.c $(TARGET)

