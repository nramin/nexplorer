build:
	mkdir -p obj
	gcc -o obj/nexplorer.out dir_list.c nexplorer.c -lncurses

build-image:
	docker build .
