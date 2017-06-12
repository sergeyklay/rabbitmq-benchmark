#include <amqp.h>

#include "logger.h"
#include "utils.h"
#include "rabbit_connection.h"

void rabbit_init_conn(amqp_connection_state_t *conn, amqp_socket_t **socket, int *status, rabbit_instance *rmq) {
	*conn = amqp_new_connection();
	*socket = amqp_tcp_socket_new(*conn);

	if (!*socket) {
		die("creating TCP socket");
	}

	*status = amqp_socket_open(*socket, rmq->address, rmq->port);
	if (*status) {
		logger_vprint(LOG_LEVEL_ERROR, "Unable to open connection to RabbitMQ server");
		die("opening TCP socket");
	}
}
