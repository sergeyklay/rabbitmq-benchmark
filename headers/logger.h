#ifndef RABBITMQ_BENCHMARK_LOGGER_H
#define RABBITMQ_BENCHMARK_LOGGER_H

#include <stdio.h>

typedef FILE *log_file_t;

typedef enum {
  LOG_LEVEL_DEBUG,
  LOG_LEVEL_INFO,
  LOG_LEVEL_NOTICE,
  LOG_LEVEL_WARNING,
  LOG_LEVEL_ERROR,
  LOG_LEVEL_FATAL
} log_level_t;

int logger_init(const char *filename);
int logger_flush(void);
void logger_vprint(log_level_t level, const char *msg, ...);

#endif // RABBITMQ_BENCHMARK_LOGGER_H
