all:
	gcc progress_bar.c -o progress_bar `pkg-config --cflags --libs gtk+-2.0`

debug:
	gcc -g progress_bar.c -o progress_bar `pkg-config --cflags --libs gtk+-2.0`

gtk3:
	gcc progress_bar.c -o progress_bar `pkg-config --cflags --libs gtk+-3.0`

run:
	./progress_bar

clean:
	rm progress_bar
