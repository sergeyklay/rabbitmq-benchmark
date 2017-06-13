#ifndef RABBITMQ_BENCHMARK_RABBIT_CONN_C_H
#define RABBITMQ_BENCHMARK_RABBIT_CONN_C_H

#include <amqp.h>
#include <amqp_tcp_socket.h>

#include "rabbit_instance.h"

int rabbit_init_conn(amqp_connection_state_t *conn, amqp_socket_t **socket, int *status, rabbit_instance *rmq);

#endif // RABBITMQ_BENCHMARK_RABBIT_CONNECTION_C_H
