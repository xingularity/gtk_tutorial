all:
	gcc menu.c -o menu `pkg-config --cflags --libs gtk+-2.0`

debug:
	gcc -g menu.c -o menu `pkg-config --cflags --libs gtk+-2.0`

run:
	./menu

clean:
	rm menu
