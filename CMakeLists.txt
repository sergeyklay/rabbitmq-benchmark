cmake_minimum_required(VERSION 3.4)
project(rabbitmq_benchmark C)

# NOTE: This CMake file is just for syntax highlighting in CLion

# amqp.h, amqp_framing.h, amqp_ssl_socket.h and amqp_tcp_socket.h
include_directories(/usr/local/include)
include_directories(./headers)

set(SOURCE_FILES
        unix/platform_utils.c
        consumer.c
        producer.c
        utils.c)

add_executable(rabbitmq_benchmark ${SOURCE_FILES})
