OBJS=avl_dictionary.o avl.o
avl_dictionary: $(OBJS)
	gcc -o avl_dictionary $(OBJS)
	
avl.o: avl.c avl.h
	gcc -c avl.c
	
avl_dictionary.o: avl_dictionary.c avl.h
	gcc -c avl_dictionary.c
