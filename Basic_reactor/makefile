CFLAGS=-g -Wall -O3 -std=c++11

object=error_handle.o event_demultiplexer.o event_handle.o \
main.o reactor.o set_nonblocking.o tcp_listen.o

basicreactor: $(object)
	g++ $(CFLAGS) -o basicreactor $(object) -I.

clean:
	rm basicreactor -f *.o
#clean:
#	rm basicreactor $(object)
