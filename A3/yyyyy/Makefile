all : a333333 

a333333 : a333333.o
	gcc -Wall -g -o a333333 a333333.o

%.o : %.c
	gcc -Wall -g -c $<

clean:
	rm -f a333333 *.o *~
