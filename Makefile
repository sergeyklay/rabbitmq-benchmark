CC=gcc
CFLAGS= -Wall -I. -I ./headers

all: clean producer consumer

producer: producer.c
	$(CC) $(CFLAGS) -o producer producer.c utils.c unix/platform_utils.c -lrabbitmq

consumer: consumer.c
	$(CC) $(CFLAGS) -o consumer consumer.c utils.c unix/platform_utils.c -lrabbitmq

clean:
	-rm -f producer consumer

.PHONY: clean
