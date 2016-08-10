CC=g++
CFLAGS=-std=c++11

app: 
	$(CC) $(CFLAGS) example.cpp -o example -lboost_system -lcrypto -lssl -lcpprest

