#ifndef RABBITMQ_BENCHMARK_COMMON_H
#define RABBITMQ_BENCHMARK_COMMON_H

#include <stdio.h>
#include <stdbool.h>

#define __OUTPUTLN__(/* const char * */ format, /* const char * */ level, /* __VA_ARGS__ */ ...) \
    do { \
        printf("[%s] " format "\n", level, ## __VA_ARGS__); \
    } while (0)

#define OUT_ERROR(format, ...) __OUTPUTLN__(format, "x", ## __VA_ARGS__)
#define OUT_INFO(format, ...) __OUTPUTLN__(format, "i", ## __VA_ARGS__)
#define OUT_USAGE() OUT_ERROR("Usage: %s <consumer|producer> configfile", argv[0]);

#endif // RABBITMQ_BENCHMARK_COMMON_H
