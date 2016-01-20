all:
	gcc spin_buttons.c -o spin_buttons `pkg-config --cflags --libs gtk+-2.0`

debug:
	gcc -g spin_buttons.c -o spin_buttons `pkg-config --cflags --libs gtk+-2.0`

gtk3:
	gcc spin_buttons.c -o spin_buttons `pkg-config --cflags --libs gtk+-3.0`

run:
	./spin_buttons

clean:
	rm spin_buttons
