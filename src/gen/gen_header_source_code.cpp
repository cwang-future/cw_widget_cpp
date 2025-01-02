
#include "gen.h"

/*生成头文件*/
void gen_h_(const char *filename, string &rethdata, const char *data)
{
	if (filename == NULL)
	{
		LOG_ERROR("filename == NULL");
		return;
	}
	
    string strtmp = filename;
    string strfilename;
    transform(strtmp.begin(), strtmp.end(), back_inserter(strfilename), ::toupper);/*转换大写*/
    string tdfilename = "__" + strfilename + "_H__";
    string sHdata = "\n#ifndef " + tdfilename + "\n";
    sHdata += "#define " + tdfilename + "\n\t\n\n";
    if(data)
    {
        sHdata += data;
        sHdata += "\n\n";
    }
    sHdata += "#endif\t/*" + tdfilename + "*/\n";
    rethdata.clear();
    rethdata = sHdata;
}

/*生成源文件*/
/*iflag = 1 C 非1 Cpp*/
void gen_c_cpp(const char *filename, string &retC_Cpp_data, const char *data, int iflag)
{
	if (filename == NULL)
	{
		LOG_ERROR("filename == NULL");
		return;
	}

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
		strC += "#include <string>\n\n";
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
	retC_Cpp_data = strC;
}

void gen_C(opt_info_t *oit)
{
	string retc, reth;
    if (oit == NULL)
	{
		LOG_ERROR("oit == NULL\n");
		return;
	}
	gen_h_(oit->argv_[0], reth, NULL);
	gen_c_cpp(oit->argv_[0], retc, NULL);
	if(write_file_data_linux(oit, retc.data(), retc.size(), ".h", 0644) != 0)
	{
		LOG_ERROR("write_file_data_linux() failed\n\n");
		return;
	}
	if(write_file_data_linux(oit, reth.data(), reth.size(), ".c", 0644) != 0)
	{
		LOG_ERROR("write_file_data_linux() failed\n\n");
		return;
	}
}

void gen_Cpp(opt_info_t *oit)
{
	string retc, reth;
	if (oit == NULL)
	{
		LOG_ERROR("oit == NULL\n");
		return;
	}
	gen_h_(oit->argv_[0], reth, NULL);
	gen_c_cpp(oit->argv_[0], retc, NULL, 0);
	if(write_file_data_linux(oit, retc.data(), retc.size(), ".h", 0644) != 0)
	{
		LOG_ERROR("write_file_data_linux() failed\n\n");
		return;
	}
	if(write_file_data_linux(oit, reth.data(), reth.size(), ".cpp", 0644) != 0)
	{
		LOG_ERROR("write_file_data_linux() failed\n\n");
		return;
	}
}
