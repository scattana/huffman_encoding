/* huff.c */
// Seth Cattanach, CSE-20289 Systems Programming Spring 2018

#include "tree.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Constants */

typedef enum {
    TSV,
    CSV,
    YAML,
    JSON,
} Format;

/* Globals */

char * PROGRAM_NAME = NULL;

// usage function
void usage(int status) {
    fprintf(stderr, "Usage: %s FILES...\n", PROGRAM_NAME);
    fprintf(stderr, "Flags:\n\n");
    fprintf(stderr, "    -f FORMAT    Output format (tsv, csv, yaml, json)\n");

    exit(status);
}


/* Functions */
// this function formats the output of tree_walk and is passed as an argument to tree_walk
void myNodeFn(const Node *n, char * encoding, void *arg){
	Format *f = (Format *)arg;
	switch(*f){
		case TSV:
			// stream results in tab-separated format
			printf("%s\t%s\t%zd\n", n->symbol.string, encoding, n->count); break;
		case CSV:
			// stream results in comma-separated format
			printf("\"%s\",\"%s\",%zd\n", n->symbol.string, encoding, n->count); break;
		case YAML:
			// stream results in YAML format
			printf("\"%s\": {\"encoding\": \"%s\", \"count\": %zd}\n", n->symbol.string, encoding, n->count); break;
		case JSON:
			// stream results in JSON format
			printf("%s\"%s\": {\"encoding\": \"%s\", \"count\": %zd},\n", "  ", n->symbol.string, encoding, n->count); break;

			break;
	}
}

// this function reads the file or stream (stdin) as specified, calls "tree_build" to create
// a Huffman encoding tree, builds the tree by pushing elements from the queue, walks (traverses)
// the tree to get the new encoding, and finally, deletes & deallocates the tree object
void rd(FILE *stream, Format f){
	Tree *t = tree_create();
	tree_build(t, stream);
	tree_walk(t, myNodeFn, &f);
	tree_delete(t);
}

// this function is called if files are passed as arguments to huff.c
// it processes the given file and passes it as the stream to the "rd" function
void cat_file(const char *path, Format f){
	FILE *fs = fopen(path, "r");
	if(fs == NULL){
		fprintf(stderr, "%s: %s: %s\n", PROGRAM_NAME, path, strerror(errno));
		return;
	}
	rd(fs, f);	// call read file function
}


/* Main Execution */
int main(int argc, char *argv[]) {
    /* Parse command line arguments */
    int argind = 1;
    Format myFormat = TSV;
    while(argind < argc && strlen(argv[argind]) > 1 && argv[argind][0] == '-'){
    	char *arg = argv[argind++];
    	switch(arg[1]){
    		case 'h':
    			usage(0); // call "usage" if "-h" flag specified
    			break;
    		case 'f':
    			if(strcmp(argv[argind],"csv")==0) myFormat = CSV;
    			if(strcmp(argv[argind],"yaml")==0) myFormat = YAML;
    			if(strcmp(argv[argind],"json")==0) myFormat = JSON;
    			argind++; // increment to avoid myFormat specifier
    			break;
    		default:
    			usage(1);
    			break;
    	}
    }

    // process each file
    if(argind==argc){
        if (myFormat == JSON) printf("%s\n","{"); 	// print out JSON format initial brace
    	rd(stdin, myFormat);
   		if (myFormat == JSON) printf("%s\n","}"); 	// print out JSON format initial brace
    }
    else{
        if (myFormat == JSON) printf("%s\n","{"); 	// print out JSON format initial brace
    	while(argind < argc){
    		char *path = argv[argind++];
    		if(strcmp(path, "-") == 0) rd(stdin, myFormat);
    		else cat_file(path, myFormat);
    	}
   		if (myFormat == JSON) printf("%s\n","}");	// print out JSON format final brace

    }
    return EXIT_SUCCESS;
}


/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
