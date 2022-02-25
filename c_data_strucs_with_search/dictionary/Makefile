
all : dictionary

dictionary : array_list.o linked_list.o stack.o queue.o bintree.o dictionary.o dictM.o
	gcc --std=c18 array_list.o linked_list.o stack.o queue.o bintree.o dictionary.o dictM.o -o dictionary

dictionary.o : dictionary.c dictionary.h
	gcc --std=c18 -Ilib -c dictionary.c -o dictionary.o

bintree.o : bintree.c bintree.h
	gcc --std=c18 -Ilib -c bintree.c -o bintree.o

stack.o : lib/stack.c lib/stack.h
	gcc --std=c18 -Ilib -c lib/stack.c -o stack.o

queue.o : lib/queue.c lib/queue.h
	gcc --std=c18 -Ilib -c lib/queue.c -o queue.o

linked_list.o : lib/linked_list.c lib/linked_list.h
	gcc --std=c18 -Ilib -c lib/linked_list.c -o linked_list.o 

array_list.o : lib/array_list.c lib/array_list.h
	gcc --std=c18 -Ilib -c lib/array_list.c -o array_list.o

clean :
	rm -f dictionary
	rm -f array_list.o linked_list.o stack.o queue.o dictionary.o
