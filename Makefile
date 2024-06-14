CC = gcc 
CFLAGS = -Wall -I.
DEPENDENCIES = hc.h

hc: main.o hc.o
	$(CC) $(CFLAGS) $^ -o $@

test: test.o hc.o 
	$(CC) $(CFLAGS) $^ -o $@

%.o : %.c 
	$(CC) -c $(CFLAGS) $^ -o $@

clean:
	rm -f *.o hc test
