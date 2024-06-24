
#include "log.h"

struct LogContex
{
	char filename[128];     /*文件名字*/
	char filenameold[136];     /*备份文件名字*/
	FILE *logfilefp;    /*写入文件的文件指针*/
	int level;  /*日志层级*/
	bool quiet; /*是否在控制台打印 true 否 false 是*/
	unsigned int filetotalsize; /*日志文件的大小*/
};
static struct LogContex L = {"", "", NULL, 1, false, 32 * 1024};

static const char *level_strings[] = 
{
	"DEBUG", "INFO", "WARN", "ERROR"
};

// static const char *level_colors[] = {
//   "\x1b[36m", "\x1b[32m", "\x1b[33m", "\x1b[31m"
// };

static void print_log(log_Event *ev) 
{
	int i = 0;
	const char *p = ev->file, *p1 = NULL;
	/*截断需要打印的文件路径*/
	while ((p1 = strstr(p, "/")) != NULL)
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
		/*fprintf(ev->fp, "%s \x1b[94m[%lu]%s[%-5s] \x1b[90m%s:%d:\x1b[0m ",
				ev->buftime, (unsigned long int)pthread_self(), level_colors[ev->level], level_strings[ev->level], p, ev->line);*/
		
	}
	else
	{
		fprintf(ev->fp, "%s [%-5s] %s:%d : ", ev->buftime, level_strings[ev->level], ev->file , ev->line);
	}
	/*格式化字符串并存储到动态分配的字符串中*/
	vfprintf(ev->fp, ev->fmt, ev->ap);
	fflush(ev->fp);
}


/*备份日志文件*/
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

/*日志属性设置
filename : 文件名字，可为NULL 
level : 设置日志层级 大于等于level的日志等级都打印 即小于level的日志等级不打印
quiet : 为 true 不打印在控制台； 为 false 打印在控制台
filetotalsize ：日志文件大小， 超过这个值将重置文件(备份现在日志文件为xx.log.old, 再次创建xx.log文件开始写日志)，当filename参数为NULL时，该值无用，可为0
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
	if (level >= DEBUG && level <= ERROR)
	{
		L.level = level;
	}
	L.quiet = quiet;
	if (filetotalsize >= 1024)
	{
		L.filetotalsize = filetotalsize;
	}
}
/*获取时间*/
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
		va_start(ev.ap, fmt);   /* 初始化可变参数列表*/
		print_log(&ev);
		va_end(ev.ap);  /* 结束可变参数列表*/
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
		va_start(ev.ap, fmt);   /* 初始化可变参数列表*/
		print_log(&ev);
		va_end(ev.ap);  /* 结束可变参数列表*/
	}
}


