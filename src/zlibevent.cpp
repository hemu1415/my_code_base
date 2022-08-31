#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>

#include <err.h>
#include <assert.h>

#include <zmq.h>
#include <event.h>
#include <evhttp.h>

struct instance {
	const char *base_url;

	struct event_base *ev_base;
	struct event ev_input;

	void *zmq_ctx;
	void *zmq_pull;
};
typedef struct instance * instance_t;

static int
input_recv(instance_t self) {
	int got_msg;
	zmq_msg_t msg;

	zmq_msg_init(&msg);
	got_msg = zmq_recv(self->zmq_pull, &msg, ZMQ_NOBLOCK) != -1;
	if( got_msg ) {
		printf(".");
		/* do something */
	}
	else {
		printf("!");
	}
	zmq_msg_close(&msg);

	return got_msg;
}

static void
input_cb(int _, short __, void *_self) {
	instance_t self = (instance_t)_self;
	uint32_t events = 0;
	size_t len = sizeof(events);

	(void)_; /* <-- 凸(⋋▂⋌)凸 --> */ (void)__;

	if( zmq_getsockopt(self->zmq_pull, ZMQ_EVENTS, &events, &len) == -1 ) {
		err(EXIT_FAILURE, "zmq_getsockopt(ZMQ_EVENTS)");
	}

	if( events & ZMQ_POLLIN ) {
		printf("D");
		while( input_recv(self) ) {
			/* nothing to see here, move along */
		}
	}
}

static int
init_pull(instance_t self, char *bind_addr) {
	int fd;
	size_t len;

	/* Bind socket */
	self->zmq_pull = zmq_socket(self->zmq_ctx, ZMQ_PULL);
	assert( self->zmq_pull != NULL );
	if( zmq_bind(self->zmq_pull, bind_addr) != 0 ) {
		err(EXIT_FAILURE, "zmq_bind(%s)", bind_addr);
	}

	/* Add ZMQ pull to event dispatcher */
	len = sizeof(self->zmq_pull);
	if( zmq_getsockopt(self->zmq_pull, ZMQ_FD, &fd, &len) == -1 ) {
		err(EXIT_FAILURE, "zmq_getsockopt(ZMQ_FD)");
	}
	event_set(&self->ev_input, fd, EV_READ | EV_PERSIST, input_cb, self);
	event_base_set(self->ev_base, &self->ev_input);

	return event_add(&self->ev_input, NULL) == 0;
}

static int
init_self(instance_t self, const char *base_url) {
	memset(self, 0, sizeof(struct instance));

	self->ev_base = event_base_new();
	self->zmq_ctx = zmq_init(1);
	self->base_url = base_url;

	return 1;
}

static int
run(instance_t self) {
	event_base_dispatch(self->ev_base);
	event_base_free(self->ev_base);
	return EXIT_SUCCESS;
}

int
main(int argc, char **argv) {
	struct instance self;
	const char *base_url = "http://derp/";

	if( argc < 2 ) {
		errx(EXIT_FAILURE, "Usage: %s <input-zmq-socket> [output-base-url]\n", basename(argv[0])); 
	}

	if( argc > 2 ) {
		if( strncmp(argv[2], "http", 4) != 0 ) {
			warnx("Invalid output-base-url, using default '%s'", base_url);
		}
		else {
			base_url = argv[1];
		}
	}

	if( ! init_self(&self, base_url)
	 || ! init_pull(&self, argv[1])
	){
		fprintf(stderr, "Error: cannot initialize!\n");
	}

	run(&self);
	return EXIT_SUCCESS;
}
