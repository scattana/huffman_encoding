CC=		gcc
CFLAGS=		-g -gdwarf-2 -Wall -std=gnu99 -fPIC
LD=		gcc
LDFLAGS=	-L.
AR=		ar
ARFLAGS=	rcs

TARGETS=	huff
TESTS=		test_node test_queue test_tree

all:		$(TARGETS)

test:		
	@curl -sLO https://gitlab.com/nd-cse-20289-sp18/cse-20289-sp18-assignments/raw/master/homework07/test_node.c
	@curl -sLO https://gitlab.com/nd-cse-20289-sp18/cse-20289-sp18-assignments/raw/master/homework07/test_queue.c
	@curl -sLO https://gitlab.com/nd-cse-20289-sp18/cse-20289-sp18-assignments/raw/master/homework07/test_tree.c
	@$(MAKE) -sk test-all

test-all:	test-node test-queue test-tree test-huff

test-node:	test_node
	@curl -sLO https://gitlab.com/nd-cse-20289-sp18/cse-20289-sp18-assignments/raw/master/homework07/test_node.sh
	@chmod +x test_node.sh
	@./test_node.sh

test-queue:	test_queue
	@curl -sLO https://gitlab.com/nd-cse-20289-sp18/cse-20289-sp18-assignments/raw/master/homework07/test_queue.sh
	@chmod +x test_queue.sh
	@./test_queue.sh

test-tree:	test_tree
	@curl -sLO https://gitlab.com/nd-cse-20289-sp18/cse-20289-sp18-assignments/raw/master/homework07/test_tree.sh
	@chmod +x test_tree.sh
	@./test_tree.sh

test-huff:	huff
	@curl -sLO https://gitlab.com/nd-cse-20289-sp18/cse-20289-sp18-assignments/raw/master/homework07/test_huff.sh
	@chmod +x test_huff.sh
	@./test_huff.sh

clean:
	@echo Cleaning...
	@rm -f $(TARGETS) $(TESTS) *.o *.a

.SUFFIXES:

# TODO: Pattern Rule for .c -> .o

%.o:	%.c
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -o $@ -c $<


# TODO: Rules for libhuff.a, test_node, test_queue, test_tree, huff

libhuff.a: node.o queue.o tree.o
	@echo Linking $@...
	@$(AR) $(ARFLAGS) $@ node.o queue.o tree.o

huff:	huff.o libhuff.a
	@echo Linking $@...
	@$(LD) $(LDFLAGS) -o $@ huff.o libhuff.a
	

#test_node:		test_node.c libhuff.a
#	@echo Compiling test_node...
#	@$(CC) $(CFLAGS) -o $@ -c $<
#	@chmod +x test_node
	
test_node.o:		test_node.c
	@echo Compiling test_node...
	@$(CC) $(CFLAGS) -o $@ -c $<
	
test_node:			test_node.o	libhuff.a
	@$(LD) $(LDFLAGS) -o $@ test_node.o libhuff.a

test_queue.o:		test_queue.c
	@echo Compiling test_queue...
	@$(CC) $(CFLAGS) -o $@ -c $<
	
test_queue:			test_queue.o libhuff.a
	@$(LD) $(LDFLAGS) -o $@ test_queue.o libhuff.a

test_tree.o:	test_tree.c
	@echo Compiling test_tree...
	@$(CC) $(CFLAGS) -o $@ -c $<
	
test_tree:		test_tree.o libhuff.a
	@$(LD) $(LDFLAGS) -o $@ test_tree.o libhuff.a

#test_tree:		test_tree.c libhuff.a
#	@echo Compiling test_tree...
#	@$(CC) $(CFLAGS) -o $@ -c $<
#	@chmod +x test_tree

