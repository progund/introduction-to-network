CHAT_OBJS=chat.o
CHAT_PROG=chat
CHAT_PROG_OBJS=chat_main.o
CFLAGS=-pedantic -Wconversion -Wall -Werror -Wextra -Wstrict-prototypes

$(CHAT_PROG): $(CHAT_OBJS) $(CHAT_PROG_OBJS) 
	gcc $(CHAT_OBJS) $(CHAT_PROG_OBJS) -o $(CHAT_PROG)

run: $(CHAT_PROG)
	./$(CHAT_PROG) localhost 1066

periodic-client:
	while (true) ; do echo -n "nc: " ; date ; sleep 2; done | nc localhost 1066

doc:
	doxygen chat.config
	cd latex && make pdf

pdf: doc

clean:
	rm -fr latex html
	rm *.o *~ *.bak $(CHAT_PROG)

stat:
	wc -l *.c *.h

valgrind:
	valgrind ./$(CHAT_PROG) localhost 1066

