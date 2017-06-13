#include <amqp.h>
#include <stdlib.h>

#include "common.h"
#include "rabbit_connection.h"

int rabbit_init_conn(amqp_connection_state_t *conn, amqp_socket_t **socket, int *status, rabbit_instance *rmq) {
	*conn = amqp_new_connection();
	*socket = amqp_tcp_socket_new(*conn);

	if (!*socket) {
		OUT_ERROR("Unable to create TCP socket");

		return EXIT_FAILURE;
	}

	*status = amqp_socket_open(*socket, rmq->address, rmq->port);
	if (*status) {
		OUT_ERROR("Unable to open connection to RabbitMQ server");

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
