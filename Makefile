c:
	gcc -c stringlib.c userfilelib.c userlib.c validationlib.c
	gcc -o c main.c stringlib.o userfilelib.o userlib.o validationlib.o
	./c.exe