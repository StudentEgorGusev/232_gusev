CC      = gcc
CFLAGS  = -Wall -Wextra -std=c2x
GEN     = gen_signals.sh
SIG_HDR = signals.h     

$(SIG_HDR): $(GEN)
	./$(GEN) > $@

killn: killn.c $(SIG_HDR)
	$(CC) $(CFLAGS) -o $@ killn.c

all: killn

clean:
	rm -f killn $(SIG_HDR)
