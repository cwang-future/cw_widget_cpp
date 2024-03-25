
#ifndef __GEN_HEADER_SOURCE_FILE_H__
#define __GEN_HEADER_SOURCE_FILE_H__
#include "common.h"
/*生成C或C++文件数据*/
/*iflag = 1 C 2 Cpp
*/
void gen_default_C_Cpp_code(string &rethdata,string &retCdata, const char *filename,int iflag);

/*iflag = 1 C 2 Cpp
*/
int gen_C_Cpp_file(const char *workpath,const char *filename,string &inHdata,string &inCdata,int iflag);

/*ihc_cpp : 1表示头文件 2表示C文件 3表示Cpp文件*/
void gen_H_C_Cpp_code(const char *filename, string &retdata, const char *data, int ihc_cpp);

#endif /*__GEN_HEADER_SOURCE_FILE_H__*/
