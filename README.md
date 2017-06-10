# RabbitMQ Benchmark

Inspiration and code from:

* https://github.com/jeffkit/rabbitmq-benchmark (Java)
* https://github.com/liuhaobupt/rabbitmq-benchmark (C)

## Get Started

### Requirements

* The [`rabbitmq-c`](https://github.com/alanxz/rabbitmq-c) client

### General Compilation

```bash
make all
```

### Usage

First you need to create test queue. For example you can use [rabbitmq-management](https://www.rabbitmq.com/management.html) plugin.

Following arquments are required to test publisher (`./producer`):

* `HOST`
* `PORT`
* `VHOST`
* `QUEUE`
* `MSGSIZE` (in bytes)
* `DURABLE`
* `MSQCOUNT`

For example:

```bash
./producer localhost 5672 "/" benchmark_queue 1024 true 100000
```

Following arquments are required to test consumer (`./consumer`):

* `HOST`
* `PORT`
* `VHOST`
* `QUEUE`
* `QOS` (prefetch count)
* `NO_ACK`

For example:

```bash
./consumer localhost 5672 "/" benchmark_queue 0 true
```

### License

This project is open source software licensed under the MIT License. See the LICENSE file for more
