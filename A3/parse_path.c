#include "ext2.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>

#include <string.h>


char **parse_file_path(char *path, int * path_size){
	int i = 0;
    int n = 0;
    // find path size
    while (path[i] != '\0') {
        if (path[i] == '/')
            n++;
        i++;
    }
    // if the path name ends with /
    if(path[i - 1] == '/') 
        n--;

    char **path_array = malloc(n * (sizeof (char *)));
	//Get each file name from path
	char *p = strtok(path, "/");
	i = 0;
	while (p != NULL){
		path_array[i] = malloc(EXT2_NAME_LEN);
		strcpy(path_array[i], p);
		i++;
		p = strtok (NULL, "/");
	}

	*path_size = n;
	return path_array;
}



int main(int argc, char *argv[]) {

	char ** path_array;
	int path_size;

	path_array = parse_file_path(argv[1], &path_size);

	printf("%d \n", path_size);

	for (int i = 0; i < path_size; i++)
		printf("%s \n", path_array[i]);



	/*
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
	*/



}





