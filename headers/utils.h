#ifndef RABBITMQ_BENCHMARK_UTILS_H
#define RABBITMQ_BENCHMARK_UTILS_H

void die(const char *fmt, ...);

extern void die_on_error(int x, char const *context);
extern void die_on_amqp_error(amqp_rpc_reply_t x, char const *context);

extern long long timeInMilliseconds(void);

#endif // RABBITMQ_BENCHMARK_UTILS_H
