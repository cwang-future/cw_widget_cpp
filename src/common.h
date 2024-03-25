
#ifndef __COMMON_H__
#define __COMMON_H__
#include <iostream>
#include <algorithm>
#include <string>
#include <stack>
#include <vector>

#include <string.h>
extern "C"
{
#include "log/log.h"
}



#define BUF_LEN_256B 256

using namespace std;

/*替换掉字符串中的-为_*/
void tihuan_(std::string &indata);
/*将数据写入到文件*/
int write_file_data(const char *filename, const char *indata, int indatasize);

// int _mkdir(const char *__path, __mode_t __mode);

#endif /*__COMMON_H__*/
