mysh:error.o mysh.o p2.o
	gcc -Wall -o myshell error.o mysh.o p2.o

p2.o:p2.c error.h mysh.h
	gcc -Wall -c p2.c

error.o:error.c error.h
	gcc -Wall -c error.c

mysh.o:mysh.h mysh.c
	gcc -Wall -c mysh.c

para:para.c

clean:
	rm *.o
