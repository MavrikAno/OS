CC = g++
CFLAGS = -lzmq

all: a b c

a: a.cpp
	$(CC) a.cpp $(CFLAGS) -o a

b: b.cpp
	$(CC) b.cpp $(CFLAGS) -o b

c: c.cpp
	$(CC) c.cpp $(CFLAGS) -o c

clean:
	rm -rf a b c