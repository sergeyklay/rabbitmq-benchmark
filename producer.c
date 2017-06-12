#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <amqp.h>
#include <amqp_tcp_socket.h>

#include "utils.h"

int main(int argc, const char *argv[]) {
	const char *host_name, *vhost, *queue_name, *user, *password;
	size_t msg_size, msg_count;
	int port, durable = 0;
	amqp_basic_properties_t props;
	amqp_connection_state_t conn_state;
	amqp_socket_t *conn_socket;
	amqp_channel_t channel_id = 1;

	if (argc < 8) {
		fprintf(stderr, "Usage: ./producer host port vhost user password queuename msgsize durable msgcount\n");
		exit(1);
	}

	host_name = argv[1];
	port = atoi(argv[2]);
	vhost = argv[3];
	user = argv[4];
	password = argv[5];
	queue_name = argv[6];

	msg_size = (size_t) atoi(argv[7]);

	if (strcmp(argv[8], "true") == 0) {
		durable = 1;
	}

	msg_count = (size_t) atoi(argv[9]);

	char *msg_body = malloc(msg_size);
	if (msg_body == NULL) {
		fprintf(stderr, "malloc error, try to reduce the msgsize parameter\n");
		exit(1);
	}
	memset(msg_body, 'x', msg_size);

	conn_state = amqp_new_connection();
	conn_socket = amqp_tcp_socket_new(conn_state);

	if (amqp_socket_open(conn_socket, host_name, port)) {
		die("Unable to open connection to RabbitMQ server");
	}

	die_on_amqp_error(amqp_login(conn_state, vhost, 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, user, password),
					  "Logging in");
	amqp_channel_open(conn_state, channel_id);
	die_on_amqp_error(amqp_get_rpc_reply(conn_state), "Opening channel");

	if (durable) {
		props._flags = AMQP_BASIC_DELIVERY_MODE_FLAG;
		props.delivery_mode = 2;
	}

	int i, j;
	long long start = timeInMilliseconds();
	for (i = 0; i < msg_count / 10000; i++) {
		long long innerStart = timeInMilliseconds();
		for (j = 0; j < 10000; j++) {
			die_on_error(
				amqp_basic_publish(
					conn_state,
					channel_id,
					amqp_cstring_bytes(""),
					amqp_cstring_bytes(queue_name),
					0,
					0,
					&props,
					amqp_cstring_bytes(msg_body)
				),
				"Publishing"
			);
		}

		long long innerEnd = timeInMilliseconds();
		printf("round %d takes %lld millseconds(10000 messages published every round)\n", i, innerEnd - innerStart);
	}

	long long end = timeInMilliseconds();
	printf("It takes %lld millseconds to send %zu messages to queue\n", end - start, msg_count);

	die_on_amqp_error(amqp_channel_close(conn_state, 1, AMQP_REPLY_SUCCESS), "Closing channel");
	die_on_amqp_error(amqp_connection_close(conn_state, AMQP_REPLY_SUCCESS), "Closing connection");
	die_on_error(amqp_destroy_connection(conn_state), "Ending connection");

	return 0;
}
