all:
	gcc fixed_container.c -o fixed_container `pkg-config --cflags --libs gtk+-2.0`

debug:
	gcc -g fixed_container.c -o fixed_container `pkg-config --cflags --libs gtk+-2.0`

run:
	./fixed_container

clean:
	rm fixed_container
