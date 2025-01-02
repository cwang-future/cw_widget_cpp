
#ifndef __GEN_H__
#define __GEN_H__
#include "common.h"

void gen_h_(const char *filename, string &rethdata, const char *data);
void gen_c_cpp(const char *filename, string &retC_Cpp_data, const char *data, int iflag = 1);

void gen_thread_code(opt_info_t *oit);
void gen_C(opt_info_t *oit);
void gen_Cpp(opt_info_t *oit);
void gen_project(opt_info_t *oit);

#endif /*__GEN_H__*/
