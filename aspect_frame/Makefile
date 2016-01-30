all:
	gcc aspect_frame.c -o aspect_frame `pkg-config --cflags --libs gtk+-2.0`

debug:
	gcc -g aspect_frame.c -o aspect_frame `pkg-config --cflags --libs gtk+-2.0`

run:
	./aspect_frame

clean:
	rm aspect_frame
