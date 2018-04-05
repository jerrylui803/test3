all : ext2_ls 

ext2_ls : ext2_ls.o
	gcc -Wall -g -o ext2_ls ext2_ls.o

%.o : %.c
	gcc -Wall -g -c $<

clean:
	rm -f a333333 *.o *~
