
#include <dirent.h>
#include "tool.h"

/*获取文件后缀名*/
static void get_suffix(const char *indata, string &suffix)
{
    string strsuf = indata;
    size_t ipos = strsuf.find_last_of(".");
    if (ipos != string::npos)
    {
        suffix = strsuf.substr(ipos + 1, strsuf.size() - 1);
    }
    else
    {
        suffix.clear();
    }
}


void tool_getpath(opt_info_t *oit)
{
	if (oit == NULL)
	{
		LOG_ERROR("oit == NULL\n");
		return;
	}
	string stroutpath;
	DIR* dir;
	struct dirent* ptr = NULL;
	stack<string> stadir;

	string path;
	if (oit->argc > 1)
	{
		path = oit->argv_[1];
	}
	else
	{
		path = oit->pwd_path;
	}
	
	int ih = 0, ic = 0, icpp = 0, icc = 0;
	stadir.push(path);
	stroutpath.clear();

	while (stadir.empty() == 0)
	{
		int flag = 0;
		path = stadir.top();
		stadir.pop();
		dir = opendir(path.data());/*打开目录*/
		if(dir == NULL)
		{
			perror("opendir() error");
			exit(1);
		}
		
		while((ptr = readdir(dir)) != NULL)//循环读取目录
		{
			/*过滤掉.和..，因为./是当前目录，../是当前目录*/
			if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
			{
				continue;
			}
			/*文件类型DT_DIR为目录*/
			if(ptr->d_type == DT_DIR)
			{
				string curpath = path + "/";
				curpath += ptr->d_name;
				stadir.push(curpath);
				continue;
			}
			/*文件类型DT_REG为普通文件*/
			if(ptr->d_type == DT_REG)
			{
				string suffix;
				get_suffix(ptr->d_name,suffix);
				if ((suffix.size() > 0) && 
					(suffix.compare("h") == 0 || suffix.compare("c") == 0 || suffix.compare("cpp") == 0 || suffix.compare("cc") == 0))
				{
					if (suffix.compare("h") == 0)
					{
						ih++;
					}
					if (suffix.compare("c") == 0)
					{
						ic++;
					}
					if (suffix.compare("cpp") == 0)
					{
						icpp++;
					}
					if (suffix.compare("cc") == 0)
					{
						icc++;
					}
					
					if (flag == 0)
					{
						stroutpath += path;
						stroutpath += "\n";
					}
					string curpath = "\t";
					curpath += path + "/";
					curpath += ptr->d_name;
					curpath += "\n";
					stroutpath += curpath;
					flag = 1;
				}
			}
		}
		if (flag == 1)
		{
			stroutpath += "\n";
		}
		closedir(dir);
	}
	
	if(stroutpath.size() == 0)
	{
		cout << "There is no '.h .c .cc .cpp' file in the [" << oit->pwd_path << "] working path.\n" << endl;
		return;
	}
	char tmp[256];
	snprintf(tmp, sizeof(tmp), "total:\n\t.h=%d, .c=%d, .cc=%d, .cpp=%d\n", ih, ic, icc, icpp);
	stroutpath += tmp;
	if(write_file_data_linux(oit, stroutpath.data(), stroutpath.size(), ".txt", 0644) != 0)
	{
		LOG_ERROR("write_file_data_linux() failed\n\n");
		return;
	}
	cout << "total:" << endl;
	cout << "\t.h=" << ih << ", .c=" << ic << ", .cc=" << icc << ", .cpp=" << icpp << endl;
}

