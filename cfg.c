#include <unistd.h>
#include <libconfig.h>
#include <stdlib.h>

#include "common.h"
#include "cfg.h"

int cfg_init(config_t *cfg, const char *filename) {
	if (access(filename, F_OK) == -1) {
		OUT_ERROR("The configuration file %s doesn't exist", filename);

		return EXIT_FAILURE;
	}

	if (access(filename, R_OK) == -1) {
		OUT_ERROR("The configuration file %s is not readable", filename);

		return EXIT_FAILURE;
	}

	config_init(cfg);

	return EXIT_SUCCESS;
}

int cfg_read(config_t *cfg, const char *filename) {
	if (!config_read_file(cfg, filename)) {
		OUT_ERROR("Syntax error in %s (line %d) -> %s",
				  config_error_file(cfg),
				  config_error_line(cfg),
				  config_error_text(cfg));

		return EXIT_FAILURE;
	}

	OUT_INFO("Using the %s configuration file", filename);

	return EXIT_SUCCESS;
}
