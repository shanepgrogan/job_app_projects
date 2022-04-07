
all : dictionary

dictionary : array_list.o linked_list.o stack.o queue.o bintree.o dictionary.o dictM.o
	gcc --std=c18 array_list.o linked_list.o stack.o queue.o bintree.o dictionary.o dictM.o -o dictionary

dictionary.o : dictionary.cpp dictionary.h
	gcc --std=c18 -Ilib -c dictionary.cpp -o dictionary.o

bintree.o : bintree.cpp bintree.h
	gcc --std=c18 -Ilib -c bintree.cpp -o bintree.o

stack.o : lib/stack.cpp lib/stack.h
	gcc --std=c18 -Ilib -c lib/stack.cpp -o stack.o

queue.o : lib/queue.cpp lib/queue.h
	gcc --std=c18 -Ilib -c lib/queue.cpp -o queue.o

linked_list.o : lib/linked_list.cpp lib/linked_list.h
	gcc --std=c18 -Ilib -c lib/linked_list.cpp -o linked_list.o 

array_list.o : lib/array_list.cpp lib/array_list.h
	gcc --std=c18 -Ilib -c lib/array_list.cpp -o array_list.o

clean :
	rm -f dictionary
	rm -f array_list.o linked_list.o stack.o queue.o dictionary.o
