all:
	gcc dialog.c -o dialog `pkg-config --cflags --libs gtk+-2.0`

debug:
	gcc -g dialog.c -o dialog `pkg-config --cflags --libs gtk+-2.0`

gtk3:
	gcc dialog.c -o dialog `pkg-config --cflags --libs gtk+-3.0`

run:
	./dialog

clean:
	rm dialog
