// Readme.txt

There should be 3 files in this directory: A5.c A5.h Readme.txt

To compile the program and produce the executable, enter the following:
		gcc -o A5 A5.c -lpthread -lrt

Run the executable by entering ./A5

You will be prompted to enter some input, which should be of the form:
		BoundedBuffer [sleep time] [number of producers] [number of consumers]

When you hit enter, it will begin printing the producer and consumer states.	
