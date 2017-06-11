PRODUCER           = producer
CONSUMER           = consumer
TARGET             = $(PRODUCER) $(CONSUMER)
CC                 = gcc
CFLAGS             += -march=native -mtune=native -Wall -fstack-protector-all -Wstack-protector -g -O2 -I. -I./headers

LIBCONFIG_INCLUDES  = $(shell pkg-config --cflags libconfig)
LIBCONFIG_LINK      = $(shell pkg-config --libs libconfig)

all: $(TARGET)

$(PRODUCER): logger.o cfg.o utils.o platform_utils.o
	$(CC) $(CFLAGS) logger.o cfg.o utils.o platform_utils.o $(PRODUCER).c -o $(PRODUCER) -lrabbitmq $(LIBCONFIG_LINK)

$(CONSUMER): utils.o platform_utils.o
	$(CC) $(CFLAGS) utils.o platform_utils.o $(CONSUMER).c -o $(CONSUMER) -lrabbitmq

utils.o:
	$(CC) $(CFLAGS) -c $(basename $(notdir $@)).c -o "$@"

platform_utils.o:
	$(CC) $(CFLAGS) -c $(basename $(notdir $@)).c -o "$@"

logger.o:
	$(CC) $(CFLAGS) -c $(basename $(notdir $@)).c -o "$@"

cfg.o: logger.o
	$(CC) $(LIBCONFIG_INCLUDES) $(CFLAGS) $< -c $(basename $(notdir $@)).c -o "$@" $(LIBCONFIG_LINK)

clean:
	-rm -rf $(PRODUCER) $(CONSUMER) *.o *.dSYM

.PHONY: clean
