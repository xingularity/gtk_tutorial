all:
	gcc toggle_button.c -o toggle_button `pkg-config --cflags --libs gtk+-2.0`

gtk3:
	gcc toggle_button.c -o toggle_button `pkg-config --cflags --libs gtk+-3.0`

run:
	./toggle_button

clean:
	rm toggle_button
