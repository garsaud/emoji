CFLAGS=-Wall -Os
CC=gcc ${CFLAGS}
DESTDIR=/usr/local/bin
DESTDATABASE=/var/lib/emoji/database.csv

.PHONY: all
all: emoji

emoji:
	${CC} -DDATABASE_FILE='"${DESTDATABASE}"' -o $@ *.c

clean:
	rm -f ./emoji

install:
	install ./emoji -D --mode 755 --target-directory "${DESTDIR}"
	install ./database.csv -D --mode 644 --target-directory "${DESTDATABASE}"
