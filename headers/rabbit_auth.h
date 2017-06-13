#ifndef RABBITMQ_BENCHMARK_RABBIT_AUTH_H
#define RABBITMQ_BENCHMARK_RABBIT_AUTH_H

#include <amqp.h>

#include "rabbit_instance.h"

int rmq_auth(amqp_connection_state_t *conn, rabbit_instance *rmq);

#endif //RABBITMQ_BENCHMARK_RABBIT_AUTH_H
