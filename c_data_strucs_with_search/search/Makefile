
all : search bfs dfs

search : linked_list.o stack.o queue.o search.o searchM.o
	gcc --std=c18 linked_list.o stack.o queue.o search.o searchM.o -o search

bfs : linked_list.o stack.o queue.o search.o bfsM.o
	gcc --std=c18 linked_list.o stack.o queue.o search.o bfsM.o -o bfs

dfs : linked_list.o stack.o queue.o search.o dfsM.o
	gcc --std=c18 linked_list.o stack.o queue.o search.o dfsM.o -o dfs

search.o : bintree.c bintree.h
	gcc --std=c18 -Ilib -c bintree.c -o search.o

stack.o : lib/stack.c lib/stack.h
	gcc --std=c18 -Ilib -c lib/stack.c -o stack.o

queue.o : lib/queue.c lib/queue.h
	gcc --std=c18 -Ilib -c lib/queue.c -o queue.o

linked_list.o : lib/linked_list.c lib/linked_list.h
	gcc --std=c18 -Ilib -c lib/linked_list.c -o linked_list.o 

clean :
	rm -f search
	rm -f linked_list.o stack.o queue.o search.o
