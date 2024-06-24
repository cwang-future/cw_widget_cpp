
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


#include "common.h"
#include "gen_header_source_code.h"
#include "gen_cmake_compile_code.h"
#include "gen_thread_code.h"
#include "get_path.h"
/*
功能：
1.生成C语言一套文件
2.生成C++一套文件
3.生成一个工程
*/


typedef struct __opt__
{
    /*
    project_type_flag的值：
    0其他 
    1创建工程 
    2创建单个文件 
    3生成pthread的api 
    4获取当前路径下的所有文件的路径写入到get_path_.txt文件中
    */
    int project_type_flag;          
    int cpp_or_c;                   /*1创建C文件 2创建Cpp文件*/
    char project_name[BUF_LEN_256B];/*工程名*/
    char file_name[BUF_LEN_256B];   /*文件名*/

    char pwd_path[BUF_LEN_256B];    /*当前工作路径*/
}opt_info_t;

opt_info_t opt;


/*初始化默认参数*/
static void opt_init(int argc, char **argv)
{
    opt.project_type_flag = 0; /*0其他*/
    opt.cpp_or_c = 1;      /*1创建C文件 2创建Cpp文件*/
    strncpy(opt.project_name, "test-project", BUF_LEN_256B);/*默认工程名*/
    strncpy(opt.file_name, "main", BUF_LEN_256B);           /*默认文件名*/
    
    /*获取当前工作路径*/
    if(getcwd(opt.pwd_path, BUF_LEN_256B) == NULL)
    {
        LOG_ERROR("Failed to obtain the current working path! [ getcwd() error]");
        exit(-1);
    }
    if(argc > 1)
    {
        if(strcmp(argv[1], "pth") == 0)
        {
            opt.cpp_or_c = 1;
            opt.project_type_flag = 3;
            strncpy(opt.file_name, "thread_api", BUF_LEN_256B);           /*默认文件名*/
            return;
        }
        else if(strcmp(argv[1], "path") == 0)
        {
            opt.project_type_flag = 4;
            strncpy(opt.file_name, "get_path_.txt", BUF_LEN_256B); 
            return;
        }
    }
    
    
    int ch;
    int ierr = 0;
    while ((ch = getopt(argc, argv, "p:c:n:h")) != -1) 
    {
        switch(ch) 
        {
        case 'c':
        {
            if(ierr == 1)
            {
                LOG_ERROR("Failed: - n and - c can only specify one.");
                exit(-1);
            }
            ierr = 1;
            if(opt.project_type_flag != 1)
            {
                opt.project_type_flag = 2;
            }
            
            opt.cpp_or_c = 1;
            string s1 = optarg;
            tihuan_(s1);
            strncpy(opt.file_name,s1.data(),255);
            break;
        }
        case 'n':
        {
            if(ierr == 1)
            {
                LOG_ERROR("Failed: - n and - c can only specify one.");
                exit(-1);
            }
            ierr = 1;
            if(opt.project_type_flag != 1)
            {
                opt.project_type_flag = 2;
            }
            opt.cpp_or_c = 2;
            string s1 = optarg;
            tihuan_(s1);
            strncpy(opt.file_name,s1.data(),255);
            break;
        }
        case 'p':
        {
            opt.project_type_flag = 1;
            strncpy(opt.project_name,optarg,255);
            break;
        }
        case 'h':
        {
            cout << "cw-widget-cpp parameter Description:\n\
-c: Generate C language. h and. c files, using this parameter followed by the name of the file to be generated\n\
    for example: cw-widget-cpp -c ctest\n\
-n: Generate .h and .cpp files, using this parameter followed by the name of the file to be generated\n\
    for example: cw-widget-cpp -n cpptest\n\
-p: Generate a project, using this parameter followed by the name of the project to be generated\n\
    for example: cw-widget-cpp -p testproject or cw-widget-cpp -p testproject -c ctest\n\
pth: API for generating Linux C threads\n\
    for example: cw-widget-cpp pth\n\
path: Obtain the absolute path of the '.h .c .cpp' file under the current working path\n\
    for example: cw-widget-cpp pth\n";
            exit(-1);
        }
        default:
            printf("Please enter cw-widget-cpp -h\n");
            exit(-1);
        break;
        }
    }

}

/*生成一个cmake的工程*/
static void generate_project(const char *workpath)
{
    const char *buff = workpath;
    if(buff == NULL)
    {
        return;
    }
    string propath = buff;
    propath += "//";
    propath += opt.project_name;
    
    int iret = mkdir(propath.data(), 0777);
    if(iret == -1)
    {
        LOG_ERROR("The [ %s ] create fail!", propath.data());
        return;
    }
    string srcpath = propath + "//src";
    iret = mkdir(srcpath.data(), 0777);
    if(iret == -1)
    {
        LOG_ERROR("The [ %s ] create fail!", srcpath.data());
        return;
    }
    string cmakedata, cmakepath, compiledata, compilepath, codeHdata, codeCdata, codepath;
    /*cmake*/
    genCMakefiledata(cmakedata, opt.project_name);
    gencompiledata(compiledata);

    cmakepath = propath + "//CMakeLists.txt";
    write_file_data(cmakepath.data(), cmakedata.data(), cmakedata.size());

    compilepath = propath + "//compile.sh";
    write_file_data(compilepath.data(), compiledata.data(), compiledata.size());

    /*C/C源码部分*/
    gen_default_C_Cpp_code(codeHdata,codeCdata, opt.file_name, opt.cpp_or_c);
    gen_C_Cpp_file(srcpath.data(), opt.file_name, codeHdata, codeCdata, opt.cpp_or_c);
    
}


/*指定参数*/
void run_opt()
{
    if(opt.project_type_flag == 1)
    {
        generate_project(opt.pwd_path);
        cout << "file save path : in " << opt.pwd_path << endl;
    }
    else if(opt.project_type_flag == 2)
    {
        /*生成单个C或C++文件*/
        string codeHdata, codeCdata, srcpath = opt.pwd_path;
        gen_default_C_Cpp_code(codeHdata, codeCdata, opt.file_name, opt.cpp_or_c);
        gen_C_Cpp_file(srcpath.data(), opt.file_name, codeHdata, codeCdata, opt.cpp_or_c);
        cout << "file save path : in " << srcpath << endl;
    }
    else if(opt.project_type_flag == 3)
    {
        string pth, retdata, tmp;
        gen_thread_code(pth);
        gen_H_C_Cpp_code(opt.file_name, retdata, pth.data(), 2);
        gen_C_Cpp_file(opt.pwd_path, opt.file_name, tmp, pth, 1);
        cout << "file save path : in " << opt.pwd_path << endl;
    }
    else if(opt.project_type_flag == 4)
    {
        string stroutpath, filepath = opt.pwd_path;
        filepath += "/";
        filepath += opt.file_name;
        getpath(opt.pwd_path, stroutpath);
        if(stroutpath.size() == 0)
        {
            cout << "There is no '.h .c .cpp' file in the [" << opt.pwd_path << "] working path." << endl;
            return;
        }
        write_file_data(filepath.data(), stroutpath.data(), stroutpath.size());
        cout << "file save path : in " << opt.pwd_path << "/" << opt.file_name << endl;
    }
    else
    {
        LOG_ERROR("Unable to identify the type of project that needs to be generated. [ project_type_flag ] : %d", opt.project_type_flag);
    }
    
}

/*其他更多功能*/
void rum_more_funcation()
{
    printf("==========================================================\n");
    printf("1、Generate C language reading and writing file data code.\n");
    printf("2、Generate Linux C thread code.\n");
    printf("==========================================================\n");
    
}



int main(int argc, char **argv)
{
    log_attribute_set(NULL, 0, 0, 0);
    opt_init(argc, argv);
    
    if(opt.project_type_flag > 0)
    {
        run_opt();
    }
    else
    {
        printf("Please enter the correct parameters.\nor\nPlease enter cw-widget-cpp -h\n");
        //rum_more_funcation();
    }
    return 0;
}

