all:
	gcc button_box.c -o button_box `pkg-config --cflags --libs gtk+-2.0`

debug:
	gcc -g button_box.c -o button_box `pkg-config --cflags --libs gtk+-2.0`

run:
	./button_box

clean:
	rm button_box
