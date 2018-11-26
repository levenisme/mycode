CCFLAGS=--std=gnu++98 -ggdb3 -pedantic -Wall -Werror -ggdb3
myShell: myShell.o 
	g++ -o myShell $(CCFLAGS) myShell.o 

%.o: %.cpp myShell.h
	g++ -c $(CCFLAGS) $<

clean:
	rm -f *.o  *~ intArrayTest
