#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "common.h"

int main(int argc, char *argv[], char **env_var_ptr) {
	if (argc < 3) {
		OUT_USAGE();
		return EXIT_FAILURE;
	}

	if (strcmp(argv[1], "consumer") != 0 && strcmp(argv[1], "producer") != 0) {
		OUT_USAGE();
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void bench_consumer() {
	// @TODO
}

void bench_producer() {
	// @TODO
}
