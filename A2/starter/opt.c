#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"

extern int memsize;

extern int debug;

extern struct frame *coremap;

extern char *tracefile;

static int time;

#define MAXLINE 256





struct node{
	struct node* next;
	struct node* curr; // used only during initialization
	int call_time;
};


struct node *frame_list = NULL;


void next_vaddr_ref(addr_t vaddr){
	// create a new node
	struct node *new_node = malloc(sizeof(struct node));
	new_node -> call_time = time;
	new_node -> next = NULL;

	time = time + 1;
	if (vaddr > memsize){
		printf("FAIL");

	}
	else{
		printf("Success");
	}
	fflush(stdout);
	// if this is the first time this address is referenced
	if(frame_list[vaddr].curr == NULL){
		return;
		frame_list[vaddr].curr = new_node;

	} 
	// else this is not the first time
	else {
		return;
		(frame_list[vaddr].curr)->next = new_node;
		(frame_list[vaddr].curr) = (frame_list[vaddr].curr)->next;
	}

}









/* Page to evict is chosen using the optimal (aka MIN) algorithm. 
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */
int opt_evict() {
	int idx = (int)(random() % memsize);
	
	return idx;
	
	return 0;
}

/* This function is called on each access to a page to update any information
 * needed by the opt algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void opt_ref(pgtbl_entry_t *p) {

	return;
}

/* Initializes any data structures needed for this
 * replacement algorithm.
 */
void opt_init() {
	

	time = 0;
	// each element is a struct, the index is the vaddr
	// each element is a node, the node contains the next
	// time that this vaddr is used
	frame_list = malloc(memsize * sizeof(struct node));
	int i = 0;
	for(i = 0; i < memsize; i++){
		frame_list[i].curr = NULL;
	}




	// read the entire swap file first to set up the OPT algorithm
	// below is basically copied from sim.c
	FILE *tfp = stdin;
	if(tracefile != NULL) {
		if((tfp = fopen(tracefile, "r")) == NULL) {
			perror("Error opening tracefile:");
			exit(1);
		}
	}
	// copied from sim.c
	// the following is the replay_trace function
	char buf[MAXLINE];
	addr_t vaddr = 0;
	char type;

	while(fgets(buf, MAXLINE, tfp) != NULL) {
		if(buf[0] != '=') {
			sscanf(buf, "%c %lx", &type, &vaddr);
			if(debug)  {
				printf("%c %lx\n", type, vaddr);
			}
			next_vaddr_ref(vaddr); // it was access_mem before, but we don't care about the type of access
		} else {
			continue;
		}

	}


}








