all:
	gcc notebook.c -o notebook `pkg-config --cflags --libs gtk+-2.0`

debug:
	gcc -g notebook.c -o notebook `pkg-config --cflags --libs gtk+-2.0`

run:
	./notebook

clean:
	rm notebook
