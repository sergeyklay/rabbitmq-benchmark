#include <string.h>
#include <stdlib.h>
#include <libconfig.h>

#include "common.h"
#include "rabbit_configure.h"
#include "rabbit_instance.h"

void rcfg_get_address(config_t *cfg, char *partname, rabbit_instance *rmq) {
	const char *str_tmp = NULL;
	size_t len_str = 0;
	char *item = NULL;

	RABBIT_CONFIGURE_GET_ITEM_NAME(item, partname, "address");

	if (config_lookup_string(cfg, item, &str_tmp)) {
		len_str = strlen(str_tmp) + 1;
		rmq->address = calloc(len_str, sizeof(char));
		strncpy(rmq->address, str_tmp, len_str - 1);
	} else {
		rmq->address = strndup("127.0.0.1", 9);
		OUT_INFO("Unable to get the RabbitMQ address, used default '127.0.0.1'");
	}

	free(item);
}

void rcfg_get_port(config_t *cfg, char *partname, rabbit_instance *rmq) {
	int port;
	char *item = NULL;

	RABBIT_CONFIGURE_GET_ITEM_NAME(item, partname, "port");

	if (config_lookup_int(cfg, item, &port)) {
		rmq->port = (short unsigned int) (port);
	} else {
		OUT_INFO("Unable to get the RabbitMQ port, used default '5672'");
	}

	free(item);
}

void rcfg_get_vhost(config_t *cfg, char *partname, rabbit_instance *rmq) {
	const char *str_tmp = NULL;
	size_t len_str = 0;
	char *item = NULL;

	RABBIT_CONFIGURE_GET_ITEM_NAME(item, partname, "vhost");

	if (config_lookup_string(cfg, item, &str_tmp)) {
		len_str = strlen(str_tmp) + 1;
		rmq->vhost = calloc(len_str, sizeof(char));
		strncpy(rmq->vhost, str_tmp, len_str - 1);
	} else {
		rmq->vhost = strndup("/", 1);
		OUT_INFO("Unable to get the RabbitMQ vhost, used default '/'");
	}

	free(item);
}

void rcfg_get_username(config_t *cfg, char *partname, rabbit_instance *rmq) {
	const char *str_tmp = NULL;
	size_t len_str = 0;
	char *item = NULL;

	RABBIT_CONFIGURE_GET_ITEM_NAME(item, partname, "username");

	if (config_lookup_string(cfg, item, &str_tmp)) {
		len_str = strlen(str_tmp) + 1;
		rmq->username = calloc(len_str, sizeof(char));
		strncpy(rmq->username, str_tmp, len_str - 1);
	} else {
		rmq->username = strndup("guest", 5);
		OUT_INFO("Unable to get the RabbitMQ username, used default 'guest'");
	}

	free(item);
}

void rcfg_get_password(config_t *cfg, char *partname, rabbit_instance *rmq) {
	const char *str_tmp = NULL;
	size_t len_str =0;
	char *item = NULL;

	RABBIT_CONFIGURE_GET_ITEM_NAME(item, partname, "password");

	if (config_lookup_string(cfg, item, &str_tmp)) {
		len_str = strlen(str_tmp) + 1;
		rmq->password = calloc(len_str, sizeof(char));
		strncpy(rmq->password, str_tmp, len_str - 1);
	} else {
		rmq->password = strndup("guest", 5);
		OUT_INFO("Unable to get the RabbitMQ password, used default 'guest'");
	}

	free(item);
}

void rcfg_get_queue(config_t *cfg, char *partname, rabbit_instance *rmq) {
	const char *str_tmp = NULL;
	size_t len_str =0;
	char *item = NULL;

	RABBIT_CONFIGURE_GET_ITEM_NAME(item, partname, "queue");

	if (config_lookup_string(cfg, item, &str_tmp)) {
		len_str = strlen(str_tmp) + 1;
		rmq->queue = calloc(len_str, sizeof(char));
		strncpy(rmq->queue, str_tmp, len_str - 1);
	} else {
		rmq->queue = strndup("benchmark_queue", 15);
		OUT_INFO( "Unable to get the RabbitMQ queue, used default 'benchmark_queue'");
	}

	free(item);
}
