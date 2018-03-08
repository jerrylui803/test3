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

addr_t *phys_frame;

#define MAXLINE 256





struct node{
	struct node* next;
	addr_t vaddr;
	int call_time;
};

// linked list, ordered by call time
// and vaddr is also stored in the node
struct node *root = NULL;
// Note that curr is only needed during init
// so that there is no need to traversing the whole list again
struct node *curr = NULL; 


void next_vaddr_ref(addr_t vaddr){
	// create a new node
	struct node *new_node = malloc(sizeof(struct node));
	new_node->vaddr = vaddr;
	new_node->next = NULL;

	time = time + 1; // fix this

	if (!root){
		root = new_node;
		curr = new_node;
	}
	else {
		curr->next = new_node;
		curr = new_node;
	}

}









/* Page to evict is chosen using the optimal (aka MIN) algorithm. 
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */
int opt_evict() {

	int i;
	int curr_time = 0;
	int max_time = 0;
	int max_time_frame_index = 0;
	int inf_time;
	// for each frame in the physical memory
	for (i = 0; i < memsize; i++){
		addr_t curr_vaddr = phys_frame[i];
		curr_time = 0;
		struct node *curr = root;
		inf_time = 1;

		// check if the virtual address in the i-th frame will ever be accessed again,
		// if yes, check when was it accessed, since we want to find the frame
		// that will be accessed the latest
		while (curr != NULL){

			if (curr->vaddr == curr_vaddr && curr_time > max_time){
				max_time = curr_time;
				max_time_frame_index = i;
				// this address stored in this frame will be accessed later
				inf_time = 0;
			}
			curr_time = curr_time + 1;
			curr = curr->next;
		}
		// if this virtual address in this frameis never accessed again, 
		// then this is the right choice, remove this frame
		if (inf_time){
			return i;
		}
	}
	return max_time_frame_index;
}







/* This function is called on each access to a page to update any information
 * needed by the opt algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void opt_ref(pgtbl_entry_t *p) {
	// update whats in the physical memory
	phys_frame[PGTBL_INDEX(p->frame)];
	// the update the linked list, so that it still
	// contains only the future memory access (sorted by early to late access time)
	struct node *to_free = root;
	root = root->next;
	free(to_free);
	return;
}

/* Initializes any data structures needed for this
 * replacement algorithm.
 */
void opt_init() {
	

	time = 0;
	// Keep a copy of the status of the physical frame
	// index is the frame number
	// each entry keep track of which vaddr is using it
	phys_frame = malloc(memsize * sizeof(addr_t));
	int i;
	for(i = 0; i < memsize; i++){
		phys_frame[i]= NULL;
	}


	// read the entire swap file first to set up the OPT algorithm
	// below is copied directly from sim.c, comments are in sim.c
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








