c:
	gcc -c stringlib.c userfilelib.c
	gcc -o c main.c stringlib.o userfilelib.o
	./c.exe