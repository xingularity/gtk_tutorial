all:
	gcc normal_button.c -o normal_button `pkg-config --cflags --libs gtk+-2.0`

gtk3:
	gcc normal_button.c -o normal_button `pkg-config --cflags --libs gtk+-3.0`

run:
	./normal_button

clean:
	rm normal_button
