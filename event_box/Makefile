all:
	gcc event_box.c -o event_box `pkg-config --cflags --libs gtk+-2.0`

debug:
	gcc -g event_box.c -o event_box `pkg-config --cflags --libs gtk+-2.0`

gtk3:
	gcc event_box.c -o event_box `pkg-config --cflags --libs gtk+-3.0`

run:
	./event_box

clean:
	rm event_box
