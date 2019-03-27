/* queue.c: Priority Queue (Min Heap) */
// Seth Cattanach, CSE-20289 Systems Programming Spring 2018

#include "debug.h"
#include "queue.h"

/* Internal Priority Queue Prototypes */

bool    queue_resize(Queue *q, size_t capacity);
void    queue_bubble_up(Queue *q, size_t i);
void    queue_bubble_down(Queue *q, size_t i);
size_t  queue_minimum_child(Queue *q, size_t i);

/* External Priority Queue Functions */

/**
 * Create Queue structure.
 * @param   capacity        Initial capacity.
 * @return  Newly allocated Queue structure with specified capacity.
 */
Queue * queue_create(size_t capacity) {
	if(capacity == 0) capacity = PRIORITY_QUEUE_CAPACITY;
	Queue * myQ = calloc(1,sizeof(Queue));
	if(myQ){
		// use predefined/default value if specified capacity is 0
		myQ->nodes = calloc(capacity, sizeof(Node*));
		myQ->size = 0;
		myQ->capacity = capacity;
	}
    return myQ;
}

/**
 * Delete Queue structure.
 * @param   q           Queue structure.
 * @return  NULL.
 */
Queue * queue_delete(Queue *q) {
	if(q){
		free(q->nodes);
		free(q);
	}
    return NULL;
}

/**
 * Push Node into Queue structure.
 * @param   q           Queue structure.
 * @param   n           Node structure.
 * @return  Whether or not the operation was successful.
 */
bool    queue_push(Queue *q, Node *n) {
	// if size equals queue's capacity, double the size of the nodes array:
	if(q->size == q->capacity){
		if(!queue_resize(q, 2*q->capacity)) return false; // +1?
	}
	// INSERT NODE AT END OF NODES ARRAY
	// BUBBLE UP WITH queue_bubble_up
	q->nodes[q->size] = n;
	queue_bubble_up(q, q->size);
	q->size++;
    return true;
}

/**
 * Pop minimum Node into Queue structure.
 * @param   q           Queue structure.
 * @return  Minimum Node structure (by count) or NULL.
 */
Node *	queue_pop(Queue *q) {
	if(q->size == 0) return NULL;
	Node * temp = q->nodes[0];	// store initial node with lowest value
	q->size--;
	q->nodes[0] = q->nodes[q->size];
	q->nodes[q->size] = NULL;	// pop the element
	queue_bubble_down(q, 0);
	//q->size--;
    return temp;
}

/**
 * Dump Queue structure.
 * @param   q           Queue structure.
 * @param   stream      I/O stream to write to.
 */
void    queue_dump(const Queue *q, FILE *stream) {
	for(size_t i=0; i < q->size; i++){
		node_dump(q->nodes[i], stream);
	}
}

/* Internal Priority Queue Functions */

/**
 * Resize Queue structure.
 * @param   q           Queue structure.
 * @param   capacity    New capacity.
 * @return  Whether or not operation succeeded.
 */
bool    queue_resize(Queue *q, size_t capacity) {
	// realloc mem to reflect new amount needed (specified by capacity param)
	q->capacity = capacity;
	q->nodes = realloc(q->nodes, (q->capacity)*sizeof(Node*));
	return q->nodes;
}

/**
 * Bubble up Node in Queue structure.
 * @param   q           Queue structure.
 * @param   i           Index to current Node structure.
 */
void    queue_bubble_up(Queue *q, size_t i) {
	while(i>0){
		if(q->nodes[i]->count < q->nodes[PARENT(i)]->count){
			Node * temp = q->nodes[PARENT(i)];
			q->nodes[PARENT(i)] = q->nodes[i];
			q->nodes[i] = temp;
		}
		i = PARENT(i);
	}
}

/**
 * Bubble down Node in Queue structure.
 * @param   q           Queue structure.
 * @param   i           Index to current Node structure.
 */
void    queue_bubble_down(Queue *q, size_t i) {
	while(LEFT_CHILD(i) < q->size){
		size_t min_index = queue_minimum_child(q, i);
		if(q->nodes[i]->count > q->nodes[min_index]->count){
			Node * temp = q->nodes[i];
			q->nodes[i] = q->nodes[min_index];
			q->nodes[min_index] = temp;
		}

		i = min_index;
	}
}

/**
 * Determines index of child with minimum value.
 * @param   q           Queue structure.
 * @param   i           Index to current Node structure.
 */
size_t  queue_minimum_child(Queue *q, size_t i) {
	size_t l = LEFT_CHILD(i), r = RIGHT_CHILD(i);
	if(!q->nodes[r]) return l;
    if(q->nodes[l]->count < q->nodes[r]->count) return l;
    else return r;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
