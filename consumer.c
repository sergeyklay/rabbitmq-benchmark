#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <amqp.h>
#include <amqp_framing.h>
#include "utils.h"

int main(int argc,const char *argv[]) {
	const char *hostName, *vhost, *queueName, *user, *password;
	int prefetchCount, sockfd, port, noAck = 1, channelId = 1;

	if (argc < 7) {
		fprintf(stderr, "Usage: ./consumer host port vhost user password queuename prefetch_count no_ack\n");
		exit(1);
	}

	hostName = argv[1];
	port = atoi(argv[2]);
	vhost = argv[3];
	user = argv[4];
	password = argv[5];
	queueName = argv[6];
	prefetchCount = atoi(argv[7]);

	if (strcmp(argv[8], "false") == 0) {
		noAck = 0;
	}

	amqp_connection_state_t conn;
	conn = amqp_new_connection();

	die_on_error(sockfd = amqp_open_socket(hostName, port), "Opening socket");
	amqp_set_sockfd(conn, sockfd);
	die_on_amqp_error(amqp_login(conn, vhost, 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, user, password), "Logging in");
	amqp_channel_open(conn, channelId);
	die_on_amqp_error(amqp_get_rpc_reply(conn), "Opening channel");

	amqp_basic_qos(conn,channelId,0,prefetchCount,0);
	amqp_basic_consume(conn,channelId,amqp_cstring_bytes(queueName),amqp_empty_bytes,0,noAck,0,amqp_empty_table);
	die_on_amqp_error(amqp_get_rpc_reply(conn), "Consuming");

	int count = 0;
	amqp_frame_t frame;
	int result;
	amqp_basic_deliver_t *d;
	amqp_basic_properties_t *p;
	size_t body_target;
	size_t body_received;

	long long start = timeInMilliseconds();
	while(1){
		{
			amqp_maybe_release_buffers(conn);
			result = amqp_simple_wait_frame(conn, &frame);
			if (result < 0)
				break;
			if (frame.frame_type != AMQP_FRAME_METHOD)
				continue;
			if (frame.payload.method.id != AMQP_BASIC_DELIVER_METHOD)
				continue;
			d = (amqp_basic_deliver_t *) frame.payload.method.decoded;
			result = amqp_simple_wait_frame(conn, &frame);
			if (result < 0)
				break;
			if (frame.frame_type != AMQP_FRAME_HEADER) {
				fprintf(stderr, "Expected header!");
				abort();
			}
			p = (amqp_basic_properties_t *) frame.payload.properties.decoded;
			body_target = frame.payload.properties.body_size;
			body_received = 0;
			while (body_received < body_target) {
				result = amqp_simple_wait_frame(conn, &frame);
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
			if(!noAck)
				amqp_basic_ack(conn,channelId,d->delivery_tag,0);
		}

		count++;
		if(count%10000 == 0) {
			long long end = timeInMilliseconds();
			fprintf(stderr,"round %d takes %lld millseconds(10000 messages consumed every round)\n",count/10000-1,end-start);
			start = timeInMilliseconds();
		}
	}


	die_on_amqp_error(amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS), "Closing channel");
	die_on_amqp_error(amqp_connection_close(conn, AMQP_REPLY_SUCCESS), "Closing connection");
	die_on_error(amqp_destroy_connection(conn), "Ending connection");

	return 0;
}
