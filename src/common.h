
#ifndef __COMMON_H__
#define __COMMON_H__
#include <iostream>
#include <algorithm>
#include <string>
#include <stack>
#include <vector>
#include <map>

#define CW_WIDGET_CPP_VERSION "V2.0.0"


#include <string.h>
extern "C"
{
	#include "log/log.h"
}

using namespace std;

#define BUF_LEN_ARG1 16
#define BUF_LEN_ARG2 32
#define BUF_LEN_256B 256


struct opt_info_t
{
	int argc;
	char exec_name[BUF_LEN_ARG1];
	char argv[BUF_LEN_ARG1][BUF_LEN_ARG2];	/*一级参数*/
	char argv_[BUF_LEN_ARG1][BUF_LEN_ARG2];	/*一级参数的值*/
	char pwd_path[BUF_LEN_256B];    /*当前工作路径*/
};

typedef void (*handle_func)(opt_info_t *oit);


enum CODE_CW
{
	CODE_PATH,
	CODE_PTH,
	CODE_C,
	CODE_N,
	CODE_P,
	CODE_H,
	CODE_MAX
};

/*替换掉字符串中的-为_*/
void tihuan_(std::string &indata);
/*将数据写入到文件*/

int write_file_data_linux(const char *filename, const char *indata, int indatasize, int _oflag);
int write_file_data_linux(opt_info_t *oit, const char *indata, int indatasize, const char *suffix, int _oflag);

// int _mkdir(const char *__path, __mode_t __mode);

#endif /*__COMMON_H__*/
