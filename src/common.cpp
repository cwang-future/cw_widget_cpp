

#include "common.h"


#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>



/*替换掉字符串中的-为_*/
void tihuan_(std::string &indata)
{
    replace(indata.begin(), indata.end(), '-', '_');
}

/*将数据写入到文件*/
int write_file_data(const char *filename, const char *indata, int indatasize)
{
    /*C语言方式实现*/
    if(indata == NULL || filename == NULL)
    {
        LOG_ERROR("indata == NULL || filename == NULL");
        return -1;
    }
    int fd = open(filename, O_WRONLY | O_CREAT | O_EXCL, 0766);
    if(fd == -1)
    {
        LOG_ERROR("The [ %s ] file open failed and it may exist!", filename);
        return -1;
    }
    if(write(fd, indata, indatasize) == -1)
    {
        LOG_ERROR("write() == -1");
        return -1;
    }
    close(fd);
    return 0;
}


// int _mkdir(const char *__path, __mode_t __mode)
// {
//     int iret = mkdir(__path,__mode);
//     if(iret == -1)
//     {
//         LOG_ERROR("The [ %s ] create fail!", __path);
//         return -1;
//     }
//     return 0;
// }