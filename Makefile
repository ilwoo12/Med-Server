all:
	g++ tcpserver.cpp -o server
	g++ tcpclient.cpp -o client

clean:
	rm -f server client *.o