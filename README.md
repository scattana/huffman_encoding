Homework 07
===========
Seth Cattanach, CSE-20289 Systems Programming Spring 2018

# Activity 2 - Questions

1. Describe how the `symbol` is stored in the `Node` **struct** by diagramming
   the memory layout of the following `Node` structure:

        Node *n = node_create('\n', 2, NULL, NULL);

    Be sure to indicate how much memory each `Node` structure occupies and how
    much is allocated for each attribute in the struct.
    
--> The Node pointer will occupy 8 bytes (64 bits), but the Node 
	struct itself will occupy 64 bits + 64 bits + 64 bits + 64 bits = 256 
	bits, which come from an int64_t, a size_t, a pointer, and another 
	pointer.
    
    1. Explain what the code `assert(n->string.letter == '\n')` would result in?
    
--> It should do nothing, because the assert statement should return true. 
	It would compare "letter" (an int64_t) to the ASCII value of the newline 
	character, and these two values should match.
    
    1. Given that `symbol` is a **union** type, is it ever possible for both the
      `letter` and `string` of the symbol `\n` to co-exist (that is, the
      `string` doesn't clobber the `letter`)?
      
--> No, the symbol '\n' would not be able to co-exist in both of these forms 
	(letter and string) for a union, because the fields of a union occupy the 
	same memory location. Since '\n' is stored in 'string' as a char array, 
	it's really storing two characters - '\' and 'n' - which don't match the 
	ASCII value of the actual newline character, '\n'.
	  

2. To construct the Huffman code, you had to utilize both a **priority queue**
   (aka. **min-heap**) and a **Huffman Tree**, both of which were binary trees.
   For the former, you used an **array** representation while for the later you
   used a **linked node** representation.  With this in mind, answer the
   following questions:

    1. Would it have been easier to implement the **priority queue** with a
      **linked node** representation?  Explain why this would be better or
      worse than the **array** representation.
      
  --> No, I believe it is better to use the array representation we used in 
  	this assignment, because - by definition - a min heap must be a complete 
  	binary tree. Therefore, for a given tree depth, we know exactly how many 
  	elements will be in the array, and further, we know the exact indicies at 
  	which the children of a node will lie (these were actually defined as 
  	macros in queue.h ... "PARENT", "LEFT_CHILD", and "RIGHT_CHILD"). 
  	It doesn't make sense to use a linked node representation, because we'd 
  	waste memory declaring and using pointers for each node. Further, it's 
  	much harder to dynamically manage memory, like we'd have to do with a 
  	linked node representation, than an array, which is guarenteed to be 
  	contiguous in memory and doesn't require dynamic memory management.

    2. Would it have been easier to implement the **Huffman Tree** with an 
      **array** representation?  Explain why this would be better or worse 
      than the **linked node** representation.
      
  --> Since the Huffman Tree isn't guarenteed to be a complete tree, it would 
  	be much harder to use an array representation, since we can't just define 
  	macros that calculate the left and right children of a node given the 
  	node index, like we did with the priority queue (heap). Since we are 
  	organizing nodes in the Huffman Tree by frequency (count) and we 
  	continuously have to swap nodes in the tree to build it correctly, it 
  	makes more sense to have a node representation - this way, we can insert 
  	nodes at arbitrary places and reassign pointers accordingly (though we do 
  	have to manually manage memory in this case).
      

3. Analyze the results of your experiements with you `huff.py` Python script.
   What sort of compression ratios were you able to achieve?  How does this
   compare to standard utilities such as `gzip`, `bzip2`, and `xz`?
   
--> In nearly all cases, my Huffman compression library compressed the input 
	files to around 55-60% of their original size. Though this seems fairly 
	good for a simple (and non-professional!) implementation, it looks like 
	most standard compression utilities are significantly more efficient. 
	"gzip," for example, has a best-case compression ratio of around 5% (of 
	original size) and an average ratio of roughly 10-15% of original size. 
	From researching online, it looks like "gzip" is the most memory 
	efficient, but not necessarily the most efficient in terms of 
	compression. "xz" seems to have the best compression ratio of these three 
	utilities (slightly better than "gzip" and much better than "bzip2"). 
	"bzip2" is has a worse compression ratio than either of the other two 
	utilities, with an average case seemingly around the 20% mark (of 
	original size). However, this is still significantly better than the ~55% 
	I was able to achieve with the "Huffman" compression in this assignment.


My "huff.py" output is pasted below for five sample texts from Project 
Gutenberg: Price and Prejudice, Alice in Wonderland, Heart of Darkness, 
Frankenstein, and Tale of Two Cities


|          FILE         |    OLD SIZE   |    NEW SIZE   |     RATIO   |
|-----------------------|---------------|---------------|-------------|
|       pride.ascii     |       5712504 |       3238750 |       56.70%|
|       alice.ascii     |       1316256 |       762209  |       57.91%|
|       heart.ascii     |       1866304 |       1065323 |       57.08%|
|       frank.ascii     |       3579728 |       2005480 |       56.02%|
|       2city.ascii     |       6298280 |       3575846 |       56.77%|




