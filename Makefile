PRODUCER           = producer
CONSUMER           = consumer
TARGET             = $(PRODUCER) $(CONSUMER)
CC                 = gcc
CFLAGS             += -march=native -mtune=native -Wall -g -O2 -I. -I./headers

all: $(TARGET)

$(PRODUCER): utils.o platform_utils.o
	$(CC) $(CFLAGS) utils.o platform_utils.o $(PRODUCER).c -o $(PRODUCER) -lrabbitmq

$(CONSUMER): utils.o platform_utils.o
	$(CC) $(CFLAGS) utils.o platform_utils.o $(CONSUMER).c -o $(CONSUMER) -lrabbitmq

utils.o:
	$(CC) $(CFLAGS) -c $(basename $(notdir $@)).c -o "$@"

platform_utils.o:
	$(CC) $(CFLAGS) -c $(basename $(notdir $@)).c -o "$@"

clean:
	-rm -rf $(PRODUCER) $(CONSUMER) *.o *.dSYM

.PHONY: clean
