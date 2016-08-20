CC=g++
CFLAGS=-std=c++11

app: 
	$(CC) $(CFLAGS) example.cpp -L /usr/local/opt/openssl/lib  -o ./app -lboost_system -lcrypto -lssl -lcpprest -lboost_thread-mt -lboost_system -lboost_chrono -lssl -lcrypto
run:
	./app
