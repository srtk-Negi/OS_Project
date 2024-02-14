shell.o: shell.c
	gcc -c shell.c -o shell.o

clean:
	rm *.o