all:
	gcc radio_buttons.c -o radio_buttons `pkg-config --cflags --libs gtk+-2.0`

gtk3:
	gcc radio_buttons.c -o radio_buttons `pkg-config --cflags --libs gtk+-3.0`

run:
	./radio_buttons

clean:
	rm radio_buttons
