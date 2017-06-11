cmake_minimum_required(VERSION 3.4)
project(rabbitmq_benchmark C)

# NOTE: This CMake file is just for syntax highlighting in CLion

# amqp*.h, amqp_framing.h, amqp_ssl_socket.h, amqp_tcp_socket.h and libconfig.h
include_directories(/usr/local/include)
include_directories(./headers)

set(SOURCE_FILES
        consumer.c
        platform_utils.c
        producer.c
        utils.c
        logger.c
        cfg.c
        rabbit_connection.c
)

add_executable(rabbitmq_benchmark ${SOURCE_FILES})
