/* node.c: Huffman Node */
// Seth Cattanach, CSE-20289 Systems Programming - Spring 2018

#include "node.h"

/* Internal Node Functions */

void    node_set_symbol(Node *n, int64_t letter);

/* External Node Functions */

/**
 * Create Node structure.
 * @param   symbol      Symbol letter.
 * @param   count       Initial count.
 * @param   left        Left Node child.
 * @param   right       Right Node child.
 * @return  Newly allocated Node structure with specified attributes.
 */
Node *  node_create(int64_t symbol, size_t count, Node *left, Node *right) {
	Node *n = malloc(sizeof(Node));
	if(n){
		node_set_symbol(n, symbol); // set symbol
		n->count = count;
		n->left = left;
		n->right = right;
		return n;
	}
    return NULL;
}

/**
 * Delete Node structure.
 * @param   n           Node structure.
 * @return  NULL.
 */
Node *  node_delete(Node *n) {
	if(n){
		node_delete(n->left);
		node_delete(n->right);
		free(n);
		//n = NULL;
    }
    return NULL;
}

/**
 * Dump Node structure.
 * @param   n           Node structure.
 * @param   stream      I/O to write to.
 */
void    node_dump(const Node *n, FILE *stream) {
	fprintf(stream,"Node{symbol: %s, count: %zu, left: 0x%lX, right: 0x%lX}\n",n->symbol.string, n->count, (uint64_t)n->left, (uint64_t)n->right);
}

/* Internal Node Functions */

/**
 * Set symbol attribute of Node structure.
 * @param   n           Node structure.
 * @param   letter      Node symbol letter value.
 */
void    node_set_symbol(Node *n, int64_t letter) {
	n->symbol.letter = letter; // set letter by int
	switch((char)letter){
		case '"':
			n->symbol.string[0] = '\\'; n->symbol.string[1] = '"';
			n->symbol.string[2] = '\0'; break;
		case '\\':
			n->symbol.string[0] = '\\'; n->symbol.string[1] = '\\';
			n->symbol.string[2] = '\0'; break;
		case '\b':
			n->symbol.string[0] = '\\'; n->symbol.string[1] = 'b';
			n->symbol.string[2] = '\0'; break;
		case '\f':
			n->symbol.string[0] = '\\'; n->symbol.string[1] = 'f';
			n->symbol.string[2] = '\0'; break;
		case '\n':
			n->symbol.string[0] = '\\'; n->symbol.string[1] = 'n';
			n->symbol.string[2] = '\0'; break;
		case '\r':
			n->symbol.string[0] = '\\'; n->symbol.string[1] = 'r';
			n->symbol.string[2] = '\0'; break;
		case '\t':
			n->symbol.string[0] = '\\'; n->symbol.string[1] = 't';
			n->symbol.string[2] = '\0'; break;
		default:
			n->symbol.string[0] = (char)letter; n->symbol.string[1] = '\0';
			break;
	} // END OF SWITCH

	// symbol.string[0] = '\"'
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
