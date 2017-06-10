SRCDIR              = $(realpath $(dir $(lastword $(filter Makefile,$(MAKEFILE_LIST)))))
PRODUCER            = producer
CONSUMER            = consumer
DEPS                = utils.o platform_utils.o
TARGET              = $(PRODUCER) $(CONSUMER)
CC                  = gcc
CFLAGS             += -Wall -g -O2 -I$(SRCDIR) -I$(SRCDIR)/headers

ifndef CXXFLAGS
CXXFLAGS = -O2 -g
endif

all: $(TARGET)

$(PRODUCER): clean $(DEPS)
	$(CC) $(CFLAGS) $(DEPS) $(PRODUCER).c -o $(PRODUCER) -lrabbitmq

$(CONSUMER): clean $(DEPS)
	$(CC) $(CFLAGS) $(DEPS) $(CONSUMER).c -o $(CONSUMER) -lrabbitmq

utils.o:
	$(CC) $(CFLAGS) -c utils.c -o "$@"

platform_utils.o:
	$(CC) $(CFLAGS) -c platform_utils.c -o "$@"

clean:
	-rm -rf $(PRODUCER) $(CONSUMER) *.o *.dSYM

.PHONY: clean
