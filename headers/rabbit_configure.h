#ifndef RABBITMQ_BENCHMARK_RABBIT_CONFIGURE_H
#define RABBITMQ_BENCHMARK_RABBIT_CONFIGURE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libconfig.h>

#include "rabbit_instance.h"

#define RABBIT_CONFIGURE_GET_ITEM_NAME(/* char * */ item, /* char * */ partname, /* const char * */ item_name) \
	do { \
		size_t len_total; \
		len_total = strlen(partname) + strlen(item_name) + 1; \
		item = calloc(len_total + 1, sizeof(char)); \
		snprintf(item, len_total + 1, "%s.%s", partname, item_name); \
	} while (0)

void rcfg_get_address(config_t *cfg, char *partname, rabbit_instance *rmq);
void rcfg_get_port(config_t *cfg, char *partname, rabbit_instance *rmq);
void rcfg_get_vhost(config_t *cfg, char *partname, rabbit_instance *rmq);
void rcfg_get_username(config_t *cfg, char *partname, rabbit_instance *rmq);
void rcfg_get_password(config_t *cfg, char *partname, rabbit_instance *rmq);
void rcfg_get_queue(config_t *cfg, char *partname, rabbit_instance *rmq);

#endif // RABBITMQ_BENCHMARK_RABBIT_CONFIGURE_H
