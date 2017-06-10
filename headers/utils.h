#ifndef librabbitmq_benchmark_utils_h
#define librabbitmq_benchmark_utils_h

void die(const char *fmt, ...);

extern void die_on_error(int x, char const *context);
extern void die_on_amqp_error(amqp_rpc_reply_t x, char const *context);

extern long long timeInMilliseconds(void);

#endif
