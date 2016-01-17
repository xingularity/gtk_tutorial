all:
	gcc table_packing.c -o table_packing `pkg-config --cflags --libs gtk+-2.0`

gtk3:
	gcc table_packing.c -o table_packing `pkg-config --cflags --libs gtk+-3.0`

run:
	./table_packing

clean:
	rm table_packing
