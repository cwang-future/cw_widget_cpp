
#include "log.h"

struct LogContex
{
	char filename[128];
	char filenameold[136];
	FILE *logfilefp;
	int level;
	bool quiet;
	unsigned int filetotalsize;
};
static struct LogContex L = {"", "", NULL, 1, false, 32 * 1024};

static const char *level_strings[] = 
{
	"DEBUG", "INFO", "WARN", "ERROR"
};

// static const char *level_colors[] = 
// {
//   "\x1b[36m", "\x1b[32m", "\x1b[33m", "\x1b[31m"
// };

static void print_log(log_Event *ev) 
{
	int i = 0;
	const char *p = ev->file, *p1 = NULL;
	while ((p != NULL) && ((p1 = strstr(p, "/")) != NULL))
	{
		p1++;
		if (p1 && (strstr(p1, "/") == NULL))
		{
			break;
		}
		p = p1;
	}
	if (p != NULL)
	{
		/*普通版*/
		fprintf(ev->fp, "%s [%-5s] %s:%d : ", ev->buftime, level_strings[ev->level], p, ev->line);
		/*线程号版*/
		// fprintf(ev->fp, "%s [%lu][%-5s] %s:%d : ", ev->buftime,  (unsigned long int)pthread_self(), level_strings[ev->level], p, ev->line);
		/*颜色版*/
		// if (ev->fp == L.logfilefp)
		// {
		// 	fprintf(ev->fp, "%s [%-5s] %s:%d : ", ev->buftime, level_strings[ev->level], p, ev->line);
		// }
		// else
		// {
		// 	fprintf(ev->fp, "%s \x1b[94m[%lu]%s[%-5s] \x1b[90m%s:%d:\x1b[0m ",
		// 		ev->buftime, (unsigned long int)pthread_self(), level_colors[ev->level], level_strings[ev->level], p, ev->line);
		// }
	}
	else
	{
		fprintf(ev->fp, "%s [%-5s] %s:%d : ", ev->buftime, level_strings[ev->level], ev->file , ev->line);
	}
	vfprintf(ev->fp, ev->fmt, ev->ap);
	fflush(ev->fp);
}

static void log_file_backup()
{
	int ret = 0;
	snprintf(L.filenameold, sizeof(L.filenameold), "%s%s", L.filename, ".old");
	ret = access(L.filename, F_OK);
	if (ret < 0) 
	{
		return;
	}

	unlink(L.filenameold);
	rename(L.filename, L.filenameold);
}

/*
例： log_attribute_set("./templog.log", 0, false, 32*1024);
	或 log_attribute_set(NULL, 0, false, 0);
*/
void log_attribute_set(const char *filename, int level, bool quiet, unsigned int filetotalsize)
{
	if (filename != NULL)
	{
		strncpy(L.filename, filename, sizeof(L.filename));
		log_file_backup();
		FILE* fp = fopen(filename, "a+");
		if (fp)
		{
			L.logfilefp = fp;
		}
	}
	if (level >= LOG__DEBUG && level <= LOG__ERROR)
	{
		L.level = level;
	}
	L.quiet = quiet;
	if (filetotalsize >= 1024)
	{
		L.filetotalsize = filetotalsize;
	}
}

static void gettime_(char* strtime, int strtime_size)
{
	struct tm tm;
	struct timespec ts;
	char buf[64] = { 0 };
	if (strtime == NULL || strtime_size <= 0)
	{
		return;
	}
	memset(strtime, 0, strtime_size);
	clock_gettime(CLOCK_REALTIME, &ts);
	localtime_r(&ts.tv_sec, &tm);
	snprintf(strtime, strtime_size, "%04d-%02d-%02d %02d:%02d:%02d.%03ld",
		tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, ts.tv_nsec / 1000000);
}

void log_log(int level, const char *file, int line, const char *fmt, ...) 
{
	struct stat s;
	log_Event ev =
	{
		.fmt = fmt,
		.file = file,
		.line = line,
		.level = level,
	};
	gettime_(ev.buftime, sizeof(ev.buftime));
	if (!L.quiet && level >= L.level) 
	{
		ev.fp = stderr;
		va_start(ev.ap, fmt);
		print_log(&ev);
		va_end(ev.ap);
	}
	if (!L.quiet && L.logfilefp && level >= L.level)
	{
		if (!stat(L.filename, &s) && s.st_size >= L.filetotalsize) 
		{
			fclose(L.logfilefp);
			rename(L.filename, L.filenameold);
			L.logfilefp = fopen(L.filename, "a+");
		}
		ev.fp = L.logfilefp;
		va_start(ev.ap, fmt);
		print_log(&ev);
		va_end(ev.ap);
	}
}


