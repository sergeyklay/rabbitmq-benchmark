#ifndef RABBITMQ_BENCHMARK_CONFIG_H
#define RABBITMQ_BENCHMARK_CONFIG_H

#include <libconfig.h>

int cfg_init(config_t *cfg, const char *filename);
int cfg_read(config_t *cfg, const char *filename);

#endif //RABBITMQ_BENCHMARK_CONFIG_H
