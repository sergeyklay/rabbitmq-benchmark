PRODUCER           = producer
CONSUMER           = consumer
TARGET             = $(PRODUCER) $(CONSUMER)
CC                 = gcc
CFLAGS             += -march=native -mtune=native -Wall -g -O2 -I. -I./headers

LIBCONFIG_INCLUDES  = $(shell pkg-config --cflags libconfig)
LIBCONFIG_LINK      = $(shell pkg-config --libs libconfig)

all: $(TARGET)

$(PRODUCER): utils.o platform_utils.o
	$(CC) $(CFLAGS) utils.o platform_utils.o $(PRODUCER).c -o $(PRODUCER) -lrabbitmq

$(CONSUMER): utils.o platform_utils.o
	$(CC) $(CFLAGS) utils.o platform_utils.o $(CONSUMER).c -o $(CONSUMER) -lrabbitmq

utils.o:
	$(CC) $(CFLAGS) -c $(basename $(notdir $@)).c -o "$@"

platform_utils.o:
	$(CC) $(CFLAGS) -c $(basename $(notdir $@)).c -o "$@"

logger.o:
	$(CC) $(CFLAGS) -c $(basename $(notdir $@)).c -o "$@"

clean:
	-rm -rf $(PRODUCER) $(CONSUMER) *.o *.dSYM

.PHONY: clean
