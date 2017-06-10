cmake_minimum_required(VERSION 3.7)
project(rabbitmq_benchmark C)

# NOTE: This CMake file is just for syntax highlighting in CLion

# amqp.h, amqp_framing.h
include_directories(/usr/local/include)

set(SOURCE_FILES
        unix/platform_utils.c
        consumer.c
        producer.c
        utils.c
        utils.h)

add_executable(rabbitmq_benchmark ${SOURCE_FILES})
