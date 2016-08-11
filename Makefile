CC=g++
CFLAGS=-std=c++11

app: 
	$(CC) $(CFLAGS) example.cpp -o ./app -lboost_system -lcrypto -lssl -lcpprest
run:
	./app
