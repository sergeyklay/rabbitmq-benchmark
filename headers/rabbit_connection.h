#ifndef RABBITMQ_BENCHMARK_RABBIT_CONN_C_H
#define RABBITMQ_BENCHMARK_RABBIT_CONN_C_H

#include <amqp.h>
#include <amqp_tcp_socket.h>

typedef struct rabbit_instance rabbit_instance;

struct rabbit_instance {
  char *hostname;
  int port;
  char *vhost;
  char *username;
  char *password;
  char *queue;
};

void rabbit_init_conn(amqp_connection_state_t *conn, amqp_socket_t **socket, int *status, rabbit_instance *rmq);
void rabbit_init_instance(rabbit_instance **rmq);
int rabbit_prepare_instance(rabbit_instance **rmq, const char *config_filename, char *partname);

#endif // RABBITMQ_BENCHMARK_RABBIT_CONNECTION_C_H
