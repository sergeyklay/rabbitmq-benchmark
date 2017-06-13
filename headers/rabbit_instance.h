#ifndef RABBITMQ_BENCHMARK_RABBIT_INSTANCE_H
#define RABBITMQ_BENCHMARK_RABBIT_INSTANCE_H

typedef struct rabbit_instance rabbit_instance;

struct rabbit_instance {
  char *address;
  int port;
  char *vhost;
  char *username;
  char *password;
  char *queue;
};

void rmq_init(rabbit_instance **rmq);
void rmq_destroy(rabbit_instance **rmq);
int rmq_prepare(rabbit_instance **rmq, const char *config_filename, char *partname);

#endif // RABBITMQ_BENCHMARK_RABBIT_INSTANCE_H
