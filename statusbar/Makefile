all:
	gcc statusbar.c -o statusbar `pkg-config --cflags --libs gtk+-2.0`

debug:
	gcc -g statusbar.c -o statusbar `pkg-config --cflags --libs gtk+-2.0`

gtk3:
	gcc statusbar.c -o statusbar `pkg-config --cflags --libs gtk+-3.0`

run:
	./statusbar

clean:
	rm statusbar
