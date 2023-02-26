sources = Tree_node.c Node_vector.c Bit_vector.c main.c

compressor:	$(sources)
	gcc -Wextra $(sources) -o compressor
