#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <amqp.h>
#include <amqp_tcp_socket.h>

#include "utils.h"

int main(int argc, const char *argv[]) {
	const char *host_name, *vhost, *queue_name, *user, *password;
	int port, result, no_ack = 1, count = 0;
	uint16_t prefetch_count;
	amqp_connection_state_t conn_state;
	amqp_socket_t *conn_socket;
	amqp_channel_t channel_id = 1;
	amqp_frame_t frame;
	amqp_basic_deliver_t *d;
	size_t body_target, body_received;

	if (argc < 7) {
		fprintf(stderr, "Usage: ./consumer host port vhost user password queuename prefetch_count no_ack\n");
		exit(1);
	}

	host_name = argv[1];
	port = atoi(argv[2]);
	vhost = argv[3];
	user = argv[4];
	password = argv[5];
	queue_name = argv[6];
	prefetch_count = (uint16_t) atoi(argv[7]);

	if (strcmp(argv[8], "false") == 0) {
		no_ack = 0;
	}

	conn_state = amqp_new_connection();
	conn_socket = amqp_tcp_socket_new(conn_state);

	if (amqp_socket_open(conn_socket, host_name, port)) {
		die("Unable to open connection to RabbitMQ server");
	}

	die_on_amqp_error(amqp_login(conn_state, vhost, 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, user, password),
					  "Logging in");
	amqp_channel_open(conn_state, channel_id);
	die_on_amqp_error(amqp_get_rpc_reply(conn_state), "Opening channel");

	amqp_basic_qos(conn_state, channel_id, 0, prefetch_count, 0);
	amqp_basic_consume(conn_state,
					   channel_id,
					   amqp_cstring_bytes(queue_name),
					   amqp_empty_bytes,
					   0,
					   no_ack,
					   0,
					   amqp_empty_table);
	die_on_amqp_error(amqp_get_rpc_reply(conn_state), "Consuming");

	long long start = timeInMilliseconds();
	while (1) {
		{
			amqp_maybe_release_buffers(conn_state);
			result = amqp_simple_wait_frame(conn_state, &frame);
			if (result < 0)
				break;
			if (frame.frame_type != AMQP_FRAME_METHOD)
				continue;
			if (frame.payload.method.id != AMQP_BASIC_DELIVER_METHOD)
				continue;
			d = (amqp_basic_deliver_t *) frame.payload.method.decoded;
			result = amqp_simple_wait_frame(conn_state, &frame);
			if (result < 0)
				break;
			if (frame.frame_type != AMQP_FRAME_HEADER) {
				fprintf(stderr, "Expected header!");
				abort();
			}

			body_target = frame.payload.properties.body_size;
			body_received = 0;
			while (body_received < body_target) {
				result = amqp_simple_wait_frame(conn_state, &frame);
				if (result < 0)
					break;
				if (frame.frame_type != AMQP_FRAME_BODY) {
					fprintf(stderr, "Expected body!");
					abort();
				}
				body_received += frame.payload.body_fragment.len;
				assert(body_received <= body_target);
			}

			if (body_received != body_target) {
				break;
			}
			if (!no_ack)
				amqp_basic_ack(conn_state, channel_id, d->delivery_tag, 0);
		}

		count++;
		if (count % 10000 == 0) {
			long long end = timeInMilliseconds();
			fprintf(
				stderr,
				"round %d takes %lld millseconds (10000 messages consumed every round)\n",
				count / 10000 - 1,
				end - start
			);
			start = timeInMilliseconds();
		}
	}

	die_on_amqp_error(amqp_channel_close(conn_state, 1, AMQP_REPLY_SUCCESS), "Closing channel");
	die_on_amqp_error(amqp_connection_close(conn_state, AMQP_REPLY_SUCCESS), "Closing connection");
	die_on_error(amqp_destroy_connection(conn_state), "Ending connection");

	return 0;
}
