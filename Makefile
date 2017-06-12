PRODUCER           = producer
CONSUMER           = consumer
TARGET             = $(PRODUCER) $(CONSUMER)
CC                 = gcc
DEPS               = logger.o cfg.o utils.o platform_utils.o rabbit_instance.o rabbit_configure.o rabbit_connection.o

LIBCONFIG_INCLUDES = $(shell pkg-config --cflags libconfig)
LINKEND_LIBS       = -lrabbitmq $(shell pkg-config --libs libconfig)

CFLAGS             += -march=native -mtune=native -Wall -fstack-protector-all -Wstack-protector -g -O2 -I. -I./headers $(LIBCONFIG_INCLUDES)

all: $(TARGET)

$(PRODUCER): $(DEPS)
	$(CC) $(CFLAGS) $(DEPS) $(PRODUCER).c -o $(PRODUCER) $(LINKEND_LIBS)

$(CONSUMER): $(DEPS)
	$(CC) $(CFLAGS) $(DEPS) $(CONSUMER).c -o $(CONSUMER) $(LINKEND_LIBS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	-rm -rf $(PRODUCER) $(CONSUMER) *.o *.dSYM

.PHONY: clean
