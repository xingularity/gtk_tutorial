all:
	gcc adj_range.c -o adj_range `pkg-config --cflags --libs gtk+-2.0`

debug:
	gcc -g adj_range.c -o adj_range `pkg-config --cflags --libs gtk+-2.0`

gtk3:
	gcc adj_range.c -o adj_range `pkg-config --cflags --libs gtk+-3.0`

run:
	./adj_range

clean:
	rm adj_range
