#include "ext2.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

int check_dir(int inodeNum, char path){

}
int main(int argc, char *argv[]) {
	char *path;
	// name of disk. (Option flag -a). path. 
	if (argc <= 2 || argc >= 5){
		fprintf(stderr, "Wrong argruments.\n");
		exit(1);
	// if without the flag
	} else if (argc == 3) {
		path = argv[2];
	// if there is a flag
	} else if (argc == 4) { 
		path = argv[3];
		if (strcmp(argv[2], "-a") != 0) {
			fprintf(stderr, "Not a vaild flag.\n");
			exit(1);
		}
	}
	if (path[0] != '/'){
		fprintf(stderr, "Not an absolute path.\n");
		exit(1);
	}
 
	int fd = open(argv[1], O_RDWR);
	unsigned char *disk;

	disk = mmap(NULL, 128 * 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd ,0);
	if (disk == MAP_FAILED) {
		perror("mmap");
		exit(1);
	}

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


	//Compare inodes with each tokenarray name?
	// root inode
	int inodeNum = EXT2_ROOT_INO;
	// run length(dirArray) times to get the coorspoin 
	struct ext2_super_block *sb = (struct ext2_super_block *) (disk + 1024);
	struct ext2_group_desc *gd = (struct ext2_group_desc *) (disk + 2048);

	//get the inode table
	struct ext2_dir_entry_2 *inotable = (struct ext2_dir_entry_2 *) (disk + 1024 * gd->bg_inode_table);
	printf("inodeTable information: \n");
	printf("%d\n",inotable->file_type);

	// TUT
	printf("Inodes: %d\n", sb->s_inodes_count);
	printf("Blocks: %d\n", sb->s_blocks_count);

	printf("Block group: \n");
	printf("     block bitmap: %d\n", gd->bg_block_bitmap);
	printf("     inode bitmap: %d\n", gd->bg_inode_bitmap);
	printf("     inode table: %d\n", gd->bg_inode_table);
	printf("     free blocks: %d\n", gd->bg_free_blocks_count);
	printf("     free inodes: %d\n", gd->bg_free_inodes_count);
	printf("     used_dirs: %d\n", gd->bg_used_dirs_count);


}
