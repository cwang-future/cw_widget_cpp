
#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <time.h>
#include<unistd.h>
#include <sys/stat.h>
/*若需要添加线程号打印，编译时请添加pthread动态库*/
// #include <pthread.h>

#define LOG_VERSION "1.0"


typedef struct 
{
	va_list ap;
	const char *fmt;
	const char *file;
	char buftime[32];
	FILE *fp;
	int line;
	int level;
	bool color;
} log_Event;



enum { DEBUG, INFO, WARN, ERROR };


#define LOG_DEBUG(...) log_log(DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...)  log_log(INFO,  __FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARN(...)  log_log(WARN,  __FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) log_log(ERROR, __FILE__, __LINE__, __VA_ARGS__)

/*日志文件一些属性设置*/
void log_attribute_set(const char* filename, int level, bool quiet, unsigned int filetotalsize);

void log_log(int level, const char *file, int line, const char *fmt, ...);

#endif