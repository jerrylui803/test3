#include "ext2.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>






int main(int argc, char *argv[]) {


	char *path = argv[1];
	//Get each file name from path
	char *p = strtok(path, "/");
	// hard code.
	char *dirArray[10];
	int i = 1;
	dirArray[0] = p;
	while (p != NULL){
		p = strtok (NULL, "/");
		dirArray[i] = p;
		i++;


	}
	int numFiles = sizeof(dirArray)/sizeof(char *);
	for (int j=0; j < numFiles; j++){
		printf("%s \n", dirArray[j]);
	}



}





