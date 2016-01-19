all:
	gcc ruler.c -o ruler `pkg-config --cflags --libs gtk+-2.0`

debug:
	gcc -g ruler.c -o ruler `pkg-config --cflags --libs gtk+-2.0`

gtk3:
	gcc ruler.c -o ruler `pkg-config --cflags --libs gtk+-3.0`

run:
	./ruler

clean:
	rm ruler
