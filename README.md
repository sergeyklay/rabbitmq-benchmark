# RabbitMQ Benchmark

Inspiration and code from:

* https://github.com/jeffkit/rabbitmq-benchmark (Java)
* https://github.com/liuhaobupt/rabbitmq-benchmark (C)

## Get Started

### Requirements

* The [`alanxz/rabbitmq-c`](https://github.com/alanxz/rabbitmq-c) client

### Compilation

To create producer and consumer use command as follows:

```bash
make
```

To create producer use:

```bash
make producer
```

To create consumer use:

```bash
make consumer
```

### Usage

First you need to create test queue. For example you can use [rabbitmq-management](https://www.rabbitmq.com/management.html) plugin.

Following arquments are required to test publisher (`./producer`):

* `HOST`
* `PORT`
* `VHOST`
* `USER`
* `PASSWORD`
* `QUEUE`
* `MSGSIZE` (in bytes)
* `DURABLE`
* `MSQCOUNT`

For example:

```bash
./producer localhost 5672 "/" user password benchmark_queue 1024 true 100000
```

Following arquments are required to test consumer (`./consumer`):

* `HOST`
* `PORT`
* `VHOST`
* `USER`
* `PASSWORD`
* `QUEUE`
* `QOS` (prefetch count)
* `NO_ACK`

For example:

```bash
./consumer localhost 5672 "/" user password benchmark_queue 0 true
```

### License

This project is open source software licensed under the MIT License. See the LICENSE file for more
