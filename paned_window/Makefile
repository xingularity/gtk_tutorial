all:
	gcc paned_window.c -o paned_window `pkg-config --cflags --libs gtk+-2.0`

debug:
	gcc -g paned_window.c -o paned_window `pkg-config --cflags --libs gtk+-2.0`

run:
	./paned_window

clean:
	rm paned_window
