#include <unistd.h>
#include <libconfig.h>

#include "logger.h"
#include "cfg.h"

int cfg_init(config_t *cfg, const char *filename)
{
	if (access(filename, F_OK) == -1) {
		logger_vprint(
			LOG_LEVEL_ERROR,
			"The configuration file %s doesn't exist",
			filename
		);

		return -1;
	}

	if (access(filename, R_OK) == -1) {
		logger_vprint(
			LOG_LEVEL_ERROR,
			"The configuration file %s is not readable",
			filename
		);

		return -1;
	}

	config_init(cfg);

	return 0;
}

int cfg_read(config_t *cfg, const char *filename)
{
	if (!config_read_file(cfg, filename)) {
		logger_vprint(
			LOG_LEVEL_ERROR,
			"Syntax error in %s (line %d) -> %s",
			config_error_file(cfg),
			config_error_line(cfg),
			config_error_text(cfg)
		);

		return -1;
	}

	logger_vprint(
		LOG_LEVEL_INFO,
		"Using the %s configuration file",
		filename
	);

	return 0;
}
