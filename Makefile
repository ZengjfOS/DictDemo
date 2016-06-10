all:
	gcc src/main.c  src/myerror.h  src/single_linked.c  src/single_linked.h -o dictDemo

clean:
	rm dictDemo
