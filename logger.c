#include <time.h>
#include <stdarg.h>

#include "logger.h"

static log_file_t log_file = NULL;

static const char *levels[] = {
	"DEBUG",
	"INFO",
	"NOTICE",
	"WARNING",
	"ERROR",
	"FATAL ERROR"
};

static struct tm *logger_localtime(void) {
	time_t now = time(0);
	return localtime(&now);
}

static void logger_print_level(log_level_t level) {
	if (log_file && level <= LOG_LEVEL_FATAL) {
		fprintf(log_file, "%s ", levels[level]);
	}
}

static void logger_print_date() {
	if (log_file) {
		char buff[20];
		struct tm *now = logger_localtime();

		strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", now);
		fprintf(log_file, "%s ", buff);
	}
}

static void logger_print_header(log_level_t level) {
	logger_print_date();
	logger_print_level(level);
}

int logger_flush(void) {
	return log_file && fclose(log_file) != EOF;
}

int logger_init(const char *file_name) {
	int ret = 0;

	if (file_name) {
		char file_path[FILENAME_MAX];

		snprintf(file_path, sizeof file_path, "%s.log", file_name);

		log_file = fopen(file_path, "a");
		ret = log_file != NULL;
	}

	return ret;
}

void logger_vprint(log_level_t level, const char *msg, ...) {
	if (log_file && msg) {
		logger_print_header(level);

		va_list argumens_list;

		va_start(argumens_list, msg);
		vfprintf(log_file, msg, argumens_list);
		va_end(argumens_list);

		fprintf(log_file, "\n");

		fflush(log_file);
	}
}
