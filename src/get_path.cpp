
#include <dirent.h>
#include "get_path.h"

/*获取文件后缀名*/
static void get_suffix(const char *indata, string &suffix)
{
    string strsuf = indata;
    int ipos = strsuf.find_last_of(".");
    if (ipos != string::npos)
    {
        suffix = strsuf.substr(ipos + 1, strsuf.size() - 1);
    }
    else
    {
        suffix.clear();
    }
}

void getpath(const char *rootpath, string &stroutpath, vector<string> * vecchillpath)
{
    DIR* dir;
    struct dirent* ptr = NULL;
    stack<string> stadir;
    string path = rootpath;
    stadir.push(path);
    stroutpath.clear();
    while (stadir.empty() == 0)
    {
        path = stadir.top();
        stadir.pop();
        dir = opendir(path.data());/*打开目录*/
        if(dir == NULL)
        {
            perror("opendir()");
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
                if(vecchillpath != NULL)
                {
                    stadir.push(curpath);
                }
                continue;
            }
            /*文件类型DT_REG为普通文件*/
            if(ptr->d_type == DT_REG)
            {
                string suffix;
                get_suffix(ptr->d_name,suffix);
                if (suffix.size() > 0 && (suffix.compare("h") == 0 || suffix.compare("c") == 0 || suffix.compare("cpp") == 0))
                {
                    string curpath = path + "/";
                    curpath += ptr->d_name;
                    curpath += "\n";
                    stroutpath += curpath;    
                }
            }
        }
    }
}

