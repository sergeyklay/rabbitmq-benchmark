#include <time.h>
#include <stdarg.h>

#include "logger.h"

static log_file_t log_file = NULL;

static const char *levels[] = {
	"Debug",
	"Info",
	"Notice",
	"Warning",
	"Error",
	"Fatal Error"
};

static struct tm *logger_localtime(void) {
	time_t t = time(NULL);
	return localtime(&t);
}

static void logger_print_level(log_level_t level) {
	if (log_file && level <= LOG_LEVEL_FATAL) {
		fprintf(log_file, "\n%s - ", levels[level]);
	}
}

static void logger_print_date() {
	if (log_file) {
		struct tm *t = logger_localtime();
		fprintf(log_file, "%dh%dm%d : ", t->tm_hour, t->tm_min, t->tm_sec);
	}
}

static void logger_print_header(log_level_t level) {
	logger_print_level(level);
	logger_print_date();
}

int logger_quit(void) {
	return log_file && fclose(log_file) != EOF;
}

int logger_init(const char *filename) {
	int ret = 0;

	if (filename) {
		char file_path[FILENAME_MAX];
		struct tm *t = logger_localtime();

		snprintf(
			file_path,
			sizeof file_path,
			"%s.%d%d%d.log",
			file_path,
			t->tm_mday,
			t->tm_mon + 1,
			t->tm_year + 1900
		);

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

		fflush(log_file);
	}
}
