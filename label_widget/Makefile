all:
	gcc label_widget.c -o label_widget `pkg-config --cflags --libs gtk+-2.0`

debug:
	gcc -g label_widget.c -o label_widget `pkg-config --cflags --libs gtk+-2.0`

gtk3:
	gcc label_widget.c -o label_widget `pkg-config --cflags --libs gtk+-3.0`

run:
	./label_widget

clean:
	rm label_widget
