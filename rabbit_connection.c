#include <amqp.h>
#include <stdlib.h>
#include <libconfig.h>

#include "logger.h"
#include "utils.h"
#include "cfg.h"
#include "rabbit_connection.h"

void rabbit_init_conn(amqp_connection_state_t *conn, amqp_socket_t **socket, int *status, rabbit_instance *rmq) {
	*conn = amqp_new_connection();
	*socket = amqp_tcp_socket_new(*conn);

	if (!*socket) {
		die("creating TCP socket");
	}

	*status = amqp_socket_open(*socket, rmq->hostname, rmq->port);
	if (*status) {
		logger_vprint(LOG_LEVEL_ERROR, "Unable to open connection to RabbitMQ server");
		die("opening TCP socket");
	}
}

void rabbit_init_instance(rabbit_instance **rmq) {
	*rmq = calloc(1, sizeof(rabbit_instance));

	(*rmq)->hostname = NULL;
	(*rmq)->port = 5672;
	(*rmq)->vhost = NULL;
	(*rmq)->username = NULL;
	(*rmq)->password = NULL;
	(*rmq)->queue = NULL;
}

int rabbit_prepare_instance(rabbit_instance **rmq, const char *config_filename, char *partname) {
	config_t config;
	logger_vprint(LOG_LEVEL_ERROR, "Initialization of RabbitMQ instance for %s", partname);

	if (cfg_init(&config, config_filename) == -1) {
		goto error;
	}

	if (cfg_read(&config, config_filename) == -1) {
		goto destroy;
	}

	rabbit_init_instance(rmq);

	config_destroy(&config);
	return 0;

  destroy:
	config_destroy(&config);
	goto error;
  error:
	return -1;
}
