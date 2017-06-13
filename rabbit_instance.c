#include <stdlib.h>
#include <libconfig.h>
#include <rabbit_configure.h>

#include "cfg.h"
#include "common.h"
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

void rmq_destroy(rabbit_instance **rmq) {
	if ((*rmq)->address)
		free((*rmq)->address);
	if ((*rmq)->vhost)
		free((*rmq)->vhost);
	if ((*rmq)->username)
		free((*rmq)->username);
	if ((*rmq)->password)
		free((*rmq)->password);
	if ((*rmq)->queue)
		free((*rmq)->queue);

	free(*rmq);
}

int rmq_prepare(rabbit_instance **rmq, const char *config_filename, char *partname) {
	config_t config;
	OUT_ERROR("Initialization of RabbitMQ instance for %s", partname);

	if (cfg_init(&config, config_filename) == EXIT_FAILURE) {
		goto error;
	}

	if (cfg_read(&config, config_filename) == EXIT_FAILURE) {
		goto destroy;
	}

	rmq_init(rmq);

	rcfg_get_address(&config, partname, *rmq);
	rcfg_get_port(&config, partname, *rmq);
	rcfg_get_vhost(&config, partname, *rmq);
	rcfg_get_username(&config, partname, *rmq);
	rcfg_get_password(&config, partname, *rmq);
	rcfg_get_queue(&config, partname, *rmq);

	config_destroy(&config);
	return EXIT_SUCCESS;

  destroy:
	config_destroy(&config);
	goto error;
  error:
	return EXIT_FAILURE;
}
