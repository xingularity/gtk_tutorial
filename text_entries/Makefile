all:
	gcc text_entries.c -o text_entries `pkg-config --cflags --libs gtk+-2.0`

debug:
	gcc -g text_entries.c -o text_entries `pkg-config --cflags --libs gtk+-2.0`

gtk3:
	gcc text_entries.c -o text_entries `pkg-config --cflags --libs gtk+-3.0`

run:
	./text_entries

clean:
	rm text_entries
