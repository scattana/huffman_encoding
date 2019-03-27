/* tree.c: Huffman Tree */
// Seth Cattanach, CSE-20289 Systems Programming Spring 2018

#include "queue.h"
#include "tree.h"
#include <stdio.h>
#include <string.h>

/* Internal Huffman Tree Prototyes */

void	tree_count(Tree *t, FILE *stream);
Queue *	tree_queue(Tree *t);
void	tree_walk_node(const Node *n, NodeFunc f, void *arg, char *encoding);

/* External Huffman Tree Functions */

/**
 * Create Tree structure.
 * @return  Newly allocated and initialized Tree structure.
 */
Tree *  tree_create() {
	Tree * myTree = calloc(1, sizeof(Tree)); // allocate and initialize to 0
	if(myTree) return myTree;
	return NULL;
}

/**
 * Delete Tree structure.
 * @param   t           Tree structure.
 * @return  NULL.
 */
Tree *  tree_delete(Tree *t) {
	node_delete(t->root);	// deallocate mem for root Node
	free(t);				// deallocate mem for Tree struct
    return NULL;
}

/**
 * Build internal Tree structure.
 * @param   t           Tree structure.
 * @param   stream      I/O stream to read from.
 * @return  Whether or not the operation succeeded.
 */
bool	tree_build(Tree *t, FILE *stream) {
	tree_count(t, stream);		// read stream and store freq in "counts"
	Queue * q = tree_queue(t);	// make new Queue with "counts" by inserting nodes
    // BUILD THE TREE
    while(q->size > 1){
    	Node * l = queue_pop(q);
    	Node * r = queue_pop(q);
    	Node * n = node_create(NODE_NOT_SYMBOL,(l->count)+(r->count), l, r);
    	bool flag = queue_push(q, n);
    	if(!flag) return false;
    }
    t->root = queue_pop(q);
    queue_delete(q);
    return true;

}

/**
 * Walk Tree structure.
 * @param   t           Tree structure.
 * @param   f           Node function.
 * @param   arg         Ndoe function argument.
 * @return  Whether or not the operation succeeded.
 */
void	tree_walk(const Tree *t, NodeFunc f, void *arg) {
	char encoding[BUFSIZ] = "";
	tree_walk_node(t->root, f, arg, encoding);
}

/* Internal Tree Functions */

/**
 * Build internal counts table in Tree structure.
 * @param   t           Tree structure.
 * @param   stream      I/O stream to read from.
 * @return
 */
void	tree_count(Tree *t, FILE *stream) {
	// need fgets in while loop?
	char line[BUFSIZ];
	while(fgets(line, BUFSIZ, stream)){
		for(int i=0; i<strlen(line); i++){
			// read in char by char to counts
			// store char count in 'counts' based on ASCII value, and increment
			//line[strcspn(line, "\n")] = 0; // remove newline character
			t->counts[(int64_t)line[i]]++;
		}

	}
}

/**
 * Create Priority Queue out of counts table in Tree structure.
 * @param   t           Tree structure.
 * @return  Priority Queue of Nodes corresponding to counts in Tree.
 */
Queue *	tree_queue(Tree *t) {
	Queue * q = queue_create(0); // queue will grow as necessary
	// loop through counts and insert new node into queue for every unique char w/nonzero count
	for(int i=0; i < TREE_COUNTS_SIZE; i++){
		if(t->counts[i] > 0){
			queue_push(q, node_create(i, t->counts[i], NULL, NULL));
		}
	}
	// CHECK IF MEM ALLOC FAILS AND HANDLE APPROPRIATELY???
    return q;
}

/**
 * Recursively walk Tree nodes.
 * @param   n           Node structure.
 * @param   f           Node function.
 * @param   arg         Node function argument.
 * @param   encoding    Node encoding.
 */
void	tree_walk_node(const Node *n, NodeFunc f, void *arg, char *encoding) {
	if(!n->left && !n->right){
		if(strlen(encoding)==0) strcat(encoding, "0");
		f(n, encoding, arg);
	}
	if(n->left){	// if n has a left child, go left
		strcat(encoding, "0"); // go left and add a "0" to the representation
		tree_walk_node(n->left, f, arg, encoding); // recursive call
		encoding[strlen(encoding)-1] = 0;	// set last element to null
	}
	if(n->right){	// if n has a left child, go left
		strcat(encoding, "1"); // go right and add a "1" to the representation
		tree_walk_node(n->right, f, arg, encoding); // recursive call
		encoding[strlen(encoding)-1] = 0;	// set last element to null
	}
} // end of tree_walk_node

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
