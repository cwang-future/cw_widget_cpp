
#include "gen.h"
#include <errno.h>


/*生成cmakelists.txt文件中的数据*/
static void genCMakefiledata(string &retdata, const char *projectname)
{
	string strdata ="\nCMAKE_MINIMUM_REQUIRED(VERSION 3.10.2)\n";
	strdata += "# 工程名\nPROJECT(";
	strdata += projectname;
	strdata += ")\n\n"
		"#########################################################################\n"
		"#							编译代码检查命令选项						  #\n"
		"#########################################################################\n"
		"# ADD_DEFINITIONS ：给gcc添加命令选项\n"
		"# -Os：相当于-O2.5。是使用了所有-O2的优化选项，但又不缩减代码尺寸的方法。\n"
		"# -Wall：打开所有警告\n"
		"# -Werror：将所有的警告转变为错误\n"
		"# -Wno-poison-system-directories：交叉编译时使用-I/usr/include等选项的警告可以使用新选项“-Wno poison system directories”禁用\n"
		"# --std=gnu99：使用gnu99来编译，对C++无效\n"
		"# -Wmissing-prototypes: 检查未声明的函数原型。\n"
		"# -Wmissing-declarations: 检查未声明的全局变量。\n"
		"# ADD_DEFINITIONS(-Os -Wall -Werror -Wmissing-declarations)\n"
		"\n"
		"#########################################################################\n"
		"#							生成可执行程序								 #\n"
		"#########################################################################\n"
		"\n"
		"# 设置可执行程序的生成目录 #\n"
		"# EXECUTABLE_OUTPUT_PATH ：需要存放的可执行程序的位置，为cmake变量\n"
		"# PROJECT_SOURCE_DIR：根目录所在路径变量，为cmake变量\n"
		"SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)\n"
		"# 打印EXECUTABLE_OUTPUT_PATH的值\n"
		"MESSAGE(STATUS \"[ EXECUTABLE_OUTPUT_PATH ] = ${EXECUTABLE_OUTPUT_PATH}\")\n"
		"\n"
		"#################\n"
		"# 设置代码外部宏 #\n"
		"#################\n"
		"# 例如：\n"
		"# SET(HELLO_WORLD \"hello world\")\n"
		"# SET(TEST_MAX_NUM 1048576)\n"
		"# ADD_DEFINITIONS( -DHELLO_WORLD=\"${HELLO_WORLD}\")\n"
		"# ADD_DEFINITIONS( -DTEST_MAX_NUM=${TEST_MAX_NUM})\n"
		"\n"
		"###################\n"
		"# 设置需要的头文件 #\n"
		"###################\n"
		"# # 清除 INCLUDE_DIR 之前的缓存\n"
		"# UNSET(INCLUDE_DIR CACHE)\n"
		"# # 在指定路径下查找 test.h\n"
		"# FIND_PATH(INCLUDE_DIR    \n"
		"	#虽然有多条路径，但只会把含当前头文件的目录加入到 INCLUDE_DIR 中\n"
		"	#NAMES test.h HINTS ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/src/test\n"
		"# )\n"
		"# MESSAGE(\"[ INCLUDE_DIR ] = ${INCLUDE_DIR}\")\n"
		"# # 设置头文件\n"
		"# INCLUDE_DIRECTORIES(\n"
		"#     ${INCLUDE_DIR}\n"
		"# )\n"
		"\n"
		"#########################\n"
		"# 设置需要编译的源码文件 #\n"
		"#########################\n"
		"# 源码存放的顶层位置文件名称\n"
		"SET(SRC_PATH  \"src\")\n"
		"\n"
		"# 设置${PROJECT_NAME}_app可执行程序需要的源码\n"
		"# 将${SRC_PATH}/*.c中的.c文件赋给ALL_SRC变量\n"
		"FILE(GLOB_RECURSE ALL_SRC  \"${SRC_PATH}/*.c\" \"${SRC_PATH}/*.cpp\")\n"
		"\n"
		"# 设置${PROJECT_NAME}_server_app可执行程序的需要的源码\n"
		"SET(COMPILE_SRC  ${ALL_SRC})\n"
		"# 假设你有不需要编译的源文件，找到该可执行文件不需要的源文件\n"
		"# FILE(GLOB_RECURSE Exclude_C_SRC  \n"
		"	#\"${SRC_PATH}/main2.c\" \n"
		"	#${SRC_PATH}/test2/*.c \n"
		"# )\n"
		"# 在COMPILE_SRC排除该可执行文件不需要的源文件\n"
		"# LIST(REMOVE_ITEM   COMPILE_SRC   ${Exclude_C_SRC} )\n"
		"MESSAGE(STATUS \"[ COMPILE_SRC ] = \" ${COMPILE_SRC})\n"
		"\n"
		"#################\n"
		"# 生成可执行程序 #\n"
		"#################\n"
		"# 生成${PROJECT_NAME}_app 程序\n"
		"ADD_EXECUTABLE(${PROJECT_NAME}_app ${COMPILE_SRC})\n"
		"\n"
		"###########################\n"
		"# 添加 可执行程序 的依赖库 #\n"
		"###########################\n"
		"# 例如：你需要添加查 ubox ubus blobmsg_json库\n"
		"# 查找库\n"
		"# FIND_LIBRARY(UBOX_LIBRARY NAMES ubox	HINTS /usr/local/lib)\n"
		"# FIND_LIBRARY(UBUS_LIBRARY NAMES ubus	HINTS /usr/local/lib)\n"
		"# FIND_LIBRARY(BLOBMSG_JSON_LIBRARY NAMES blobmsg_json	HINTS /usr/local/lib)\n"
		"\n"
		"# MESSAGE(STATUS \"[ UBOX_LIBRARY ] = ${UBOX_LIBRARY}\")\n"
		"# MESSAGE(STATUS \"[ UBUS_LIBRARY ] = ${UBUS_LIBRARY}\")\n"
		"# MESSAGE(STATUS \"[ BLOBMSG_JSON_LIBRARY ] = ${BLOBMSG_JSON_LIBRARY}\")\n"
		"\n"
		"# 设置可执行文件需要依赖的库\n"
		"TARGET_LINK_LIBRARIES(${PROJECT_NAME}_app\n"
		"	# ${UBOX_LIBRARY}\n"
		"	# ${UBUS_LIBRARY}\n"
		"	# ${BLOBMSG_JSON_LIBRARY}\n"
		")\n"
		"\n"
		"########################\n"
		"# 安装 可执行程序 到系统 #\n"
		"########################\n"
		"# 清除 CMAKE_INSTALL_PREFIX 之前的缓存\n"
		"# UNSET(CMAKE_INSTALL_PREFIX CACHE)\n"
		"# CMAKE_INSTALL_PREFIX默认值为：/usr/local\n"
		"# 命令指定：cmake -DCMAKE_INSTALL_PREFIX=/home/ubuntu/test/usr\n"
		"# 代码指定：\n"
		"# SET(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/usr)\n"
		"# MESSAGE(STATUS \"[ install BIN--CMAKE_INSTALL_PREFIX ] = \" ${CMAKE_INSTALL_PREFIX})\n"
		"# INSTALL(TARGETS ${PROJECT_NAME}_app RUNTIME DESTINATION bin)\n"
		"\n"
		"\n"
		"#########################################################################\n"
		"#								生成 lib 库								#\n"
		"#########################################################################\n"
		"\n"
		"########### 例子：###########\n"
		"\n"
		"# #LIBRARY_OUTPUT_PATH ：需要存放的库的位置，为cmake变量\n"
		"# SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)\n"
		"\n"
		"# 把所有源文件添加到列表\n"
		"# AUX_SOURCE_DIRECTORY(. DIR_LIB_SRCS)\n"
		"# 设置单个文件\n"
		"# SET(DIR_LIB_SRCS ./src/hello.c)\n"
		"# SET(DIR_MAIN ./src/main.c)\n"
		"\n"
		"# MESSAGE(STATUS \"[ DIR_LIB_SRCS ] = \" ${DIR_LIB_SRCS})\n"
		"# MESSAGE(STATUS \"[ DIR_MAIN ] = \" ${DIR_MAIN})\n"
		" \n"
		"# # 生成动态库 #\n"
		"# ADD_LIBRARY(hello SHARED ${DIR_LIB_SRCS})\n"
		"# ADD_LIBRARY(main SHARED ${DIR_MAIN})\n"
		"\n"
		"\n"
		"# 生成静态库 和 动态库名称一样 #\n"
		"# 生成静态库\n"
		"# ADD_LIBRARY(hello_static STATIC ${DIR_LIB_SRCS}) \n"
		"\n"
		"# 通过 SET_TARGET_PROPERTIES 重新命名为libhello.a\n"
		"# SET_TARGET_PROPERTIES(hello_static PROPERTIES OUTPUT_NAME \"hello\")\n"
		"# 获取相关属性也是通过 SET_TARGET_PROPERTIES  OUTPUT_NAME静态库名字\n"
		"# GET_TARGET_PROPERTY(OUTPUT_VALUE hello_static OUTPUT_NAME)\n"
		"# MESSAGE(STATUS \"STATIC_LIB_OUTPUT_NAME = \" ${OUTPUT_VALUE})\n"
		"\n"
		"# 动态库版本号设置 , VERSION指代动态库版本，SOVERSION 指代 API 版本。\n"
		"# 其中，libhello.so.1.2为动态库的文件名(realname)，libhello.so.1为动态库的别名(soname)，\n"
		"# libhello.so为动态库的链接名（linkname）。\n"
		"# SET_TARGET_PROPERTIES(hello PROPERTIES VERSION 1.2 SOVERSION 1)\n"
		"\n"
		"\n"
		"# 清除 CMAKE_INSTALL_PREFIX 之前的缓存\n"
		"# UNSET(CMAKE_INSTALL_PREFIX CACHE)\n"
		"# CMAKE_INSTALL_PREFIX默认值为：/usr/local\n"
		"# 命令指定：cmake -DCMAKE_INSTALL_PREFIX=/home/ubuntu/test/usr\n"
		"# 代码指定：\n"
		"# SET(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/usr)\n"
		"# MESSAGE(STATUS \"[ install LIB--CMAKE_INSTALL_PREFIX ] = \" ${CMAKE_INSTALL_PREFIX})\n"
		"\n"
		"\n"
		"# 安装共享库和头文件\n"
		"# 将动态库和静态库安装到 ${CMAKE_INSTALL_PREFIX}/usr/lib\n"
		"# bin lib 目录若是不存在则会创建该目录\n"
		"# INSTALL(TARGETS main hello hello_static #${PROJECT_NAME}_app\n"
		"	# RUNTIME DESTINATION bin\n"
		"	# LIBRARY DESTINATION lib\n"
		"	# ARCHIVE DESTINATION lib\n"
		"# )\n"
		"\n"
		"# # 安装头文件：将./src/hello.h ./src/main.h 文件安装到 ${CMAKE_INSTALL_PREFIX}/include\n"
		"# INSTALL(FILES ./src/hello.h ./src/main.h \n"
		"	# DESTINATION include\n"
		"# )\n"
		"\n"
		"\n"
		"# # 安装目录：将src中的所有文件安装到 ${CMAKE_INSTALL_PREFIX}/src/doc目录下\n"
		"# INSTALL(DIRECTORY src/ DESTINATION src/doc)\n"
		"\n"
		"#########################################################################\n"
		"#						需要编译子模块的CMakeLists.txt					 #\n"
		"#########################################################################\n"
		"# ADD_SUBDIRECTORY(lib)\n";
	retdata.clear();
	retdata = strdata;
}

/*生成compile.sh*/
static void gencompiledata(string &retdata)
{
	string strdata = "#!/bin/bash\nmkdir build\ncd build\ncmake ..\nmake";
	retdata.clear();
	retdata = strdata;
}

static void _gettime_(char* strtime, int strtime_size)
{
	struct tm tm;
	struct timespec ts;
	if (strtime == NULL || strtime_size <= 0)
	{
		return;
	}
	memset(strtime, 0, strtime_size);
	clock_gettime(CLOCK_REALTIME, &ts);
	localtime_r(&ts.tv_sec, &tm);
	snprintf(strtime, strtime_size, "%04d%02d%02d%02d%02d%02d",
		tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

void gen_project(opt_info_t *oit)
{
	int icpp = 0;
	int iret = 0;
	string retcmake, retcom, retc, retcpp, reth;
	string cfilename, pfilename;
	string cfilepath, hfilepath, pfilepath, srcfilepath, cmakelistspath, compilepath;
	if (oit == NULL)
	{
		LOG_ERROR("oit == NULL\n");
		return;
	}
	pfilepath = oit->pwd_path;
	
	for (int i = 0; i < oit->argc; i++)
	{
		if (strcmp("p", oit->argv[i]) == 0)
		{
			pfilename = oit->argv_[i];
			continue;
		}
		else if (strcmp("n", oit->argv[i]) == 0)
		{
			cfilename = oit->argv_[i];
			icpp = 2;
			continue;
		}
		else if (strcmp("c", oit->argv[i]) == 0)
		{
			cfilename = oit->argv_[i];
			continue;
		}
	}
	
	if (pfilename.size() > 0)
	{
		pfilepath += "/" + pfilename;
	}
	else
	{
		char tmp[128] = { 0 };
		_gettime_(tmp, 128);
		pfilename = "cw_temp_project";
		pfilepath += "/" + pfilename + "_";
		pfilepath += tmp;
	}
	// 7(r4w2x1)77
	iret = mkdir(pfilepath.data(), 0755);
	if(iret == -1)
	{
		LOG_ERROR("The [ %s ] create failed: %s\n", pfilepath.data(), strerror(errno));
		return;
	}
	srcfilepath = pfilepath + "/src";
	iret = mkdir(srcfilepath.data(), 0755);
	if(iret == -1)
	{
		LOG_ERROR("The [ %s ] create failed: %s\n", srcfilepath.data(), strerror(errno));
		return;
	}
	genCMakefiledata(retcmake, pfilename.data());
	gencompiledata(retcom);

	cmakelistspath = pfilepath + "/CMakeLists.txt";
	compilepath = pfilepath + "/compile.sh";
	if(write_file_data_linux(cmakelistspath.data(), retcmake.data(), retcmake.size(), 0644) != 0)
	{
		LOG_ERROR("write_file_data_linux() failed!\n");
		return;
	}
	if(write_file_data_linux(compilepath.data(), retcom.data(), retcom.size(), 0755) != 0)
	{
		LOG_ERROR("write_file_data_linux() failed!\n");
		return;
	}

	if (cfilename.size() > 0)
	{
		gen_h_(cfilename.data(), reth, NULL);
		hfilepath += srcfilepath + "/" + cfilename + ".h";
		if (icpp == 2)
		{
			gen_c_cpp(cfilename.data(), retc, NULL, 2);
			cfilepath = srcfilepath + "/" + cfilename + ".cpp";
		}
		else
		{
			gen_c_cpp(cfilename.data(), retc, NULL, 1);
			cfilepath = srcfilepath + "/" + cfilename + ".c";
		}
		
	}
	else
	{
		cfilename = pfilename;
		gen_h_(cfilename.data(), reth, NULL);
		gen_c_cpp(cfilename.data(), retc, NULL, 1);
		cfilepath = srcfilepath + "/" + cfilename + ".c";
		hfilepath = srcfilepath + "/" + cfilename + ".h";
	}
	// cout << pfilepath << "\n" << cmakelistspath << "\n" << compilepath << "\n" << hfilepath << "\n" << cfilepath << endl;
	
	if(write_file_data_linux(hfilepath.data(), reth.data(), reth.size(), 0644) != 0)
	{
		LOG_ERROR("write_file_data_linux() failed!\n");
		return;
	}
	if(write_file_data_linux(cfilepath.data(), retc.data(), retc.size(), 0644) != 0)
	{
		LOG_ERROR("write_file_data_linux() failed!\n");
		return;
	}
	cout << "project save path in: " << pfilepath << endl;
}