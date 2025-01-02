

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

int write_file_data_linux(const char *filename, const char *indata, int indatasize, int _oflag)
{
	if (filename == NULL || indata == NULL || indatasize <= 0)
	{
		LOG_ERROR("filename == NULL || indata == NULL || indatasize(%d) <= 0\n", indatasize);
		return -1;
	}
	int fd = open(filename, O_WRONLY | O_CREAT | O_EXCL, _oflag);
	if(fd == -1)
	{
		LOG_ERROR("The [ %s ] file open failed and it may exist!\n", filename);
		return -1;
	}
	if(write(fd, indata, indatasize) == -1)
	{
		LOG_ERROR("write() == -1\n");
		return -1;
	}
	close(fd);
	return 0;
}
int write_file_data_linux(opt_info_t *oit, const char *indata, int indatasize, const char *suffix, int _oflag)
{
	int fd = -1;
	string filepath;
	if (oit == NULL || indata == NULL || suffix == NULL || indatasize <= 0)
	{
		LOG_ERROR("oit == NULL || indata == NULL || indatasize(%d) <= 0\n", indatasize);
		return -1;
	}
	filepath = oit->pwd_path;
	filepath += "/";
	filepath += oit->argv_[0];
	filepath += suffix;

	fd = open(filepath.data(), O_WRONLY | O_CREAT | O_EXCL, _oflag);
	if(fd == -1)
	{
		LOG_ERROR("The [ %s ] file open failed and it may exist!\n", filepath.data());
		return -1;
	}
	if(write(fd, indata, indatasize) == -1)
	{
		LOG_ERROR("write() == -1\n");
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