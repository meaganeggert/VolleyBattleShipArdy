all: client server

client: client.cc
        g++ -pthread -O3 -g -o client client.cc

server: server.cc
        g++ -pthread -O3 -g -o server server.cc

clean:
        rm -f *.o a.out core
