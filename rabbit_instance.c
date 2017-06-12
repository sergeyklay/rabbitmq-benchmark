#include <stdlib.h>
#include <libconfig.h>

#include "cfg.h"
#include "logger.h"
#include "rabbit_instance.h"

void rmq_init(rabbit_instance **rmq) {
	*rmq = calloc(1, sizeof(rabbit_instance));

	(*rmq)->address = NULL;
	(*rmq)->port = 5672;
	(*rmq)->vhost = NULL;
	(*rmq)->username = NULL;
	(*rmq)->password = NULL;
	(*rmq)->queue = NULL;
}

int rmq_prepare(rabbit_instance **rmq, const char *config_filename, char *partname) {
	config_t config;
	logger_vprint(LOG_LEVEL_INFO, "Initialization of RabbitMQ instance for %s", partname);

	if (cfg_init(&config, config_filename) == -1) {
		goto error;
	}

	if (cfg_read(&config, config_filename) == -1) {
		goto destroy;
	}

	rmq_init(rmq);

	config_destroy(&config);
	return 0;

  destroy:
	config_destroy(&config);
	goto error;
  error:
	return -1;
}
