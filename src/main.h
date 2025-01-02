#ifndef __MAIN_H__
#define __MAIN_H__

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "common.h"

#include "tool.h"
#include "gen.h"


#ifndef ARRAY_SIZE
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#endif

struct handle_func_t
{
    char func_name[64];
    handle_func exec;
};

#endif /*__MAIN_H__*/