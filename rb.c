#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <amqp.h>

#include "common.h"
#include "rabbit_connection.h"
#include "rabbit_instance.h"
#include "rabbit_auth.h"

int main(int argc, char *argv[], char **env_var_ptr) {
	int status;
	rabbit_instance *rmq = NULL;
	amqp_socket_t *socket = NULL;
	amqp_connection_state_t conn;

	if (argc < 3) {
		OUT_USAGE();
		return EXIT_FAILURE;
	}

	if (strcmp(argv[1], "consumer") != 0 && strcmp(argv[1], "producer") != 0) {
		OUT_USAGE();
		return EXIT_FAILURE;
	}

	rmq_init(&rmq);

	if (rmq_prepare(&rmq, argv[2], "RABBIT") == EXIT_FAILURE) {
		OUT_ERROR("Failed to prepare rabbit instance for benchmark");
		return EXIT_FAILURE;
	}

	rabbit_init_conn(&conn, &socket, &status, rmq);

	if (rmq_auth(&conn, rmq) == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}

	if (strcmp(argv[1], "consumer") == 0) {
		OUT_ERROR("Not implemented");
		return EXIT_FAILURE;
	} else {
		OUT_ERROR("Not implemented");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
