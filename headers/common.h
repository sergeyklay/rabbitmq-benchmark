#ifndef RABBITMQ_BENCHMARK_COMMON_H
#define RABBITMQ_BENCHMARK_COMMON_H

#include <stdio.h>
#include <stdbool.h>

#define __OUTPUTLN__(/* FILE * */ fstream, /* const char * */ format, /* const char * */ level, /* __VA_ARGS__ */ ...) \
    do { \
		fprintf(fstream, "[%s] " format "\n", level, ## __VA_ARGS__); \
    } while (0)

#define OUT_ERROR(/* const char * */ format, /* __VA_ARGS__ */ ...) __OUTPUTLN__(stderr, format, "x", ## __VA_ARGS__)
#define OUT_INFO(/* const char * */ format, /* __VA_ARGS__ */ ...) __OUTPUTLN__(stdout, format, "i", ## __VA_ARGS__)
#define OUT_USAGE() OUT_INFO("Usage: %s <consumer|producer> configfile", argv[0]);

#endif // RABBITMQ_BENCHMARK_COMMON_H
