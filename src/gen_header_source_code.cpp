
#include "gen_header_source_code.h"

/*生成头文件*/
static void gen_H_(const char *filename, string &rethdata, const char *data)
{
    string strtmp = filename;
    string strfilename;
    transform(strtmp.begin(), strtmp.end(), back_inserter(strfilename), ::toupper);/*转换大写*/
    string tdfilename = "__" + strfilename + "_H__";
    string sHdata = "\n#ifndef " + tdfilename + "\n";
    sHdata += "#define " + tdfilename + "\n\n\n";
    if(data)
    {
        sHdata += data;
        sHdata += "\n\n";
    }
    sHdata += "#endif\t/*" + tdfilename + "*/\n";
    rethdata.clear();
    rethdata += sHdata;
}

/*生成源文件*/
/*iflag = 1 C 非1 Cpp*/
static void gen_C_Cpp(const char *filename, string &retC_Cpp_data, const char *data, int iflag = 1)
{
    /*生成源文件数据*/
    string strC;
    if(iflag == 1)
    {
        strC = "\n#include <stdio.h>\n";
    }
    else
    {
        strC = "\n#include <iostream>\n";
        strC += "#include <vector>\n";
    }
    strC += "#include <string.h>\n";
    strC += "#include <stdlib.h>\n\n";

    strC += "#include \"";
    strC += filename;
    strC += ".h\"\n\n";
    if(iflag != 1)
    {
        strC += "using namespace std;\n\n";
    }

    if(data)
    {
        strC += "\n";
        strC += data;
        strC += "\n\n";
    }

    strC += "int main(int argc, char **argv)\n{\n";
    if(iflag == 1)
    {
        strC += "\tprintf(\"hello world\\n\");\n\treturn 0;\n}\n";
    }
    else
    {
        strC += "\tcout << \"hello world\\n\";\n\treturn 0;\n}\n";
    }
    retC_Cpp_data.clear();
    retC_Cpp_data += strC;
}

/*生成默认的头文件和源文件的数据 C/C++*/
/*iflag = 1 C 非1 Cpp*/
void gen_default_C_Cpp_code(string &retHdata, string &retCdata, const char *filename, int iflag)
{
    /*生成头文件数据*/
    gen_H_(filename, retHdata, NULL); 
    gen_C_Cpp(filename, retCdata, NULL, iflag);
}

/*ihc_cpp : 1表示头文件 2表示C文件 3表示Cpp文件*/
void gen_H_C_Cpp_code(const char *filename, string &retdata, const char *data, int ihc_cpp)
{
    if(ihc_cpp == 1)
    {
        gen_H_(filename, retdata, data); 
    }
    else if(ihc_cpp == 2)
    {
        gen_C_Cpp(filename, retdata, data, 1);
    }
    else if(ihc_cpp == 3)
    {
        gen_C_Cpp(filename, retdata, data, 2);
    }
}

/*iflag = 1 C 2 Cpp*/
int gen_C_Cpp_file(const char *workpath, const char *filename, string &inHdata, string &inCdata, int iflag)
{
    /*获取当前工作路径*/
    const char *buff = workpath;
    if(buff == NULL)
    {
        LOG_ERROR("Failed to generate src source file!");
        return -1;
    }
    string cfilename = buff;
    cfilename += "//";
    cfilename += filename;
    if(iflag == 1)
    {
        cfilename += ".c";
    }
    else
    {
        cfilename += ".cpp";
    }
    string hfilename = buff;
    hfilename += "//";
    hfilename += filename;
    hfilename += ".h";

#if 0
    /*C++方式实现*/

    /*文件*/
    fstream fs;

        //2、写入方式打开
        fs.open(cfilename.data(), ios::out);
    if(fs)
    {
        fs << inCdata;
        fs.close();
    }
    else
    {
        cerr << "File open failed !\n";
        return -1;
    }
    
        fs.open(hfilename.data(), ios::out);
    if(fs)
    {
        fs << inHdata;
        fs.close();
    }
    else
    {
        cerr << "File open failed !\n";
        return -1;
    }
#else
    /*C语言方式实现*/
    if(inHdata.size() != 0 )write_file_data(hfilename.data(), inHdata.data(), inHdata.size());
    if(inCdata.size() != 0 )write_file_data(cfilename.data(), inCdata.data(), inCdata.size());
#endif
    return 0;
}


