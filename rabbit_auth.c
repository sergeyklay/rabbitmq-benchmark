#include <amqp.h>
#include <stdlib.h>

#include "common.h"
#include "rabbit_auth.h"
#include "rabbit_instance.h"

int rmq_auth(amqp_connection_state_t *conn, rabbit_instance *rmq) {
	amqp_rpc_reply_t reply;

	reply = amqp_login(*conn, rmq->vhost, 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, rmq->username, rmq->password);

	if (reply.reply_type == AMQP_RESPONSE_NORMAL) {
		return EXIT_SUCCESS;
	}

	switch (reply.reply_type) {
	case AMQP_RESPONSE_NONE: OUT_ERROR("No Response from RPC");
		break;
	case AMQP_RESPONSE_LIBRARY_EXCEPTION: OUT_ERROR("Possible SSL/TLS error during certificate negotiations");
		break;
	case AMQP_RESPONSE_SERVER_EXCEPTION: OUT_ERROR("Issue could be authentication or issue with the MQ Channel");
		switch (reply.reply.id) {
		case AMQP_CONNECTION_CLOSE_METHOD: {
			amqp_connection_close_t *m = (amqp_connection_close_t *) reply.reply.decoded;
			OUT_ERROR("Server connection error %d, message: %.*s\n",
					  m->reply_code,
					  (int) m->reply_text.len,
					  (char *) m->reply_text.bytes);
			break;
		}
		case AMQP_CHANNEL_CLOSE_METHOD: {
			amqp_channel_close_t *m = (amqp_channel_close_t *) reply.reply.decoded;
			OUT_ERROR("Server channel error %d, message: %.*s\n",
					  m->reply_code,
					  (int) m->reply_text.len,
					  (char *) m->reply_text.bytes);
			break;
		}
		default: OUT_ERROR("Unknown server error, method id 0x%08X\n", reply.reply.id);
			break;
		}
	default: OUT_ERROR("Unknown error, method id 0x%08X\n", reply.reply.id);
		break;
	}

	return EXIT_FAILURE;
}
