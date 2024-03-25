
#include "gen_cmake_compile_code.h"

#if 0
/*生成cmakelists.txt文件中的数据*/
void genCMakefiledata_1(string &retdata,const char *projectname)
{
  string strdata = "#版本名称\ncmake_minimum_required(VERSION 3.10.2)\n";
  strdata += "#工程名\nproject(";
  strdata += projectname;
  strdata += ")\n";
  strdata += "#设置可执行文件输出的目录\n\
#EXECUTABLE_OUTPUT_PATH可执行文件的cmake变量\n\
#PROJECT_SOURCE_DIR根目录所在路径变量\n\
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)\n\
message(STATUS \"EXECUTABLE_OUTPUT_PATH = ${EXECUTABLE_OUTPUT_PATH}\")\n\
\n\
#设置需要的头文件\n\
include_directories(\n\
)\n\
\n\
# 找库\n\
find_library(UBOX_LIBRARY NAMES ubox	HINTS /usr/local/lib)	\n\
\n\
#包含原程序,即把给定目录下的源程序复制给变量ALL_SRC\n\
#将指定路径下的源文件储存在指定的变量中\n\
file(GLOB_RECURSE Serve_SRC  \"src/*.cpp\" \"src/*.c\")\n\
message(STATUS \"Serve_SRC = ${Serve_SRC}\")\n\
\n\
#生成程序\n\
add_executable(${PROJECT_NAME}_app ${Serve_SRC})\n\
\n\
#设置可执行文件需要链接的库\n\
target_link_libraries(${PROJECT_NAME}_app\n\
#    ${UBOX_LIBRARY}\n\
)\n\
#安装到系统\n\
#INSTALL(TARGETS ${PROJECT_NAME}_app\n\
#    RUNTIME DESTINATION bin\n\
#)\n";
  retdata.clear();
  retdata = strdata;
}
#endif

/*生成cmakelists.txt文件中的数据*/
void genCMakefiledata(string &retdata,const char *projectname)
{
    string strdata = "########################################################################\n\
# 版本名称\ncmake_minimum_required(VERSION 3.10.2)\n";
    strdata += "# 工程名\nproject(";
    strdata += projectname;
    strdata += ")\n#########################################################################\n\n\
\n\
#########################################################################\n\
# 编译代码检查命令选项\n\
#########################################################################\n\
# ADD_DEFINITIONS ：给gcc添加命令选项\n\
# -Os：相当于-O2.5。是使用了所有-O2的优化选项，但又不缩减代码尺寸的方法。\n\
# -Wall：打开所有警告\n\
# -Werror：将所有的警告转变为错误\n\
# -Wno-poison-system-directories：交叉编译时使用-I/usr/include等选项的警告可以使用新选项“-Wno poison system directories”禁用\n\
# --std=gnu99：使用gnu99来编译，对C++无效\n\
# -Wmissing-prototypes: 检查未声明的函数原型。\n\
# -Wmissing-declarations: 检查未声明的全局变量。\n\
# ADD_DEFINITIONS(-Os -Wall -Werror -Wmissing-declarations)\n\
\n\
#########################################################################\n\
#                           生成 可执行程序                              #\n\
#########################################################################\n\
\n\
# 设置可执行程序的生成目录 #\n\
# EXECUTABLE_OUTPUT_PATH ：需要存放的可执行程序的位置，为cmake变量\n\
# PROJECT_SOURCE_DIR：根目录所在路径变量，为cmake变量\n\
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)\n\
# 打印EXECUTABLE_OUTPUT_PATH的值\n\
message(STATUS \"[ EXECUTABLE_OUTPUT_PATH ] = ${EXECUTABLE_OUTPUT_PATH}\")\n\
\n\
#################\n\
# 设置代码外部宏 #\n\
#################\n\
# 例如：\n\
# SET(HELLO_WORLD \"hello world\")\n\
# SET(TEST_MAX_NUM 1048576)\n\
# ADD_DEFINITIONS( -DHELLO_WORLD=\"${HELLO_WORLD}\")\n\
# ADD_DEFINITIONS( -DTEST_MAX_NUM=${TEST_MAX_NUM})\n\
\n\
###################\n\
# 设置需要的头文件 #\n\
###################\n\
# # 清除 INCLUDE_DIR 之前的缓存\n\
# unset(INCLUDE_DIR CACHE)\n\
# # 在指定路径下查找 test.h\n\
# FIND_PATH(INCLUDE_DIR    \n\
#     # 虽然有多条路径，但只会把含当前头文件的目录加入到 INCLUDE_DIR 中\n\
#     NAMES test.h HINTS ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/src/test\n\
# )\n\
# message(\"[ INCLUDE_DIR ] = ${INCLUDE_DIR}\")\n\
# # 设置头文件\n\
# INCLUDE_DIRECTORIES(\n\
#     ${INCLUDE_DIR}\n\
# )\n\
\n\
#########################\n\
# 设置需要编译的源码文件 #\n\
#########################\n\
# 源码存放的顶层位置文件名称\n\
set(SRC_PATH  \"src\")\n\
\n\
# 设置${PROJECT_NAME}_app可执行程序需要的源码\n\
# 将${SRC_PATH}/*.c中的.c文件赋给ALL_SRC变量\n\
file(GLOB_RECURSE ALL_SRC  \"${SRC_PATH}/*.c\" \"${SRC_PATH}/*.cpp\")\n\
\n\
# 设置${PROJECT_NAME}_server_app可执行程序的需要的源码\n\
set(COMPILE_SRC  ${ALL_SRC})\n\
# 假设你有不需要编译的源文件，找到该可执行文件不需要的源文件\n\
# file(GLOB_RECURSE Exclude_C_SRC  \n\
# \"${SRC_PATH}/main2.c\" \n\
#  ${SRC_PATH}/test2/*.c \n\
# )\n\
# 在COMPILE_SRC排除该可执行文件不需要的源文件\n\
# list(REMOVE_ITEM   COMPILE_SRC   ${Exclude_C_SRC} )\n\
message(STATUS \"[ COMPILE_SRC ] = \" ${COMPILE_SRC})\n\
\n\
\n\
#################\n\
# 生成可执行程序 #\n\
#################\n\
# 生成${PROJECT_NAME}_app 程序\n\
add_executable(${PROJECT_NAME}_app ${COMPILE_SRC})\n\
\n\
\n\
###########################\n\
# 添加 可执行程序 的依赖库 #\n\
###########################\n\
# 例如：你需要添加查 ubox ubus blobmsg_json库\n\
# 查找库\n\
# find_library(UBOX_LIBRARY NAMES ubox	HINTS /usr/local/lib)	\n\
# find_library(UBUS_LIBRARY NAMES ubus	HINTS /usr/local/lib)\n\
# find_library(BLOBMSG_JSON_LIBRARY NAMES blobmsg_json	HINTS /usr/local/lib)\n\
\n\
# message(STATUS \"[ UBOX_LIBRARY ] = ${UBOX_LIBRARY}\")\n\
# message(STATUS \"[ UBUS_LIBRARY ] = ${UBUS_LIBRARY}\")\n\
# message(STATUS \"[ BLOBMSG_JSON_LIBRARY ] = ${BLOBMSG_JSON_LIBRARY}\")\n\
\n\
# 设置可执行文件需要依赖的库\n\
target_link_libraries(${PROJECT_NAME}_app\n\
    # ${UBOX_LIBRARY}\n\
    # ${UBUS_LIBRARY}\n\
    # ${BLOBMSG_JSON_LIBRARY}\n\
)\n\
\n\
########################\n\
# 安装 可执行程序 到系统 #\n\
########################\n\
# 清除 CMAKE_INSTALL_PREFIX 之前的缓存\n\
# unset(CMAKE_INSTALL_PREFIX CACHE)\n\
# CMAKE_INSTALL_PREFIX默认值为：/usr/local\n\
# 命令指定：cmake -DCMAKE_INSTALL_PREFIX=/home/ubuntu/test/usr\n\
# 代码指定：\n\
# set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/usr)\n\
# message(STATUS \"[ install BIN--CMAKE_INSTALL_PREFIX ] = \" ${CMAKE_INSTALL_PREFIX})\n\
# INSTALL(TARGETS ${PROJECT_NAME}_app RUNTIME DESTINATION bin)\n\
\n\
\n\
#########################################################################\n\
#                               生成 lib 库                             #\n\
#########################################################################\n\
\n\
################### 例子：#####################\n\
\n\
# #LIBRARY_OUTPUT_PATH ：需要存放的库的位置，为cmake变量\n\
# set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)\n\
\n\
# # 把所有源文件添加到列表\n\
# # aux_source_directory(. DIR_LIB_SRCS)\n\
# # 设置单个文件\n\
# set(DIR_LIB_SRCS ./src/hello.c)\n\
# set(DIR_MAIN ./src/main.c)\n\
\n\
# message(STATUS \"[ DIR_LIB_SRCS ] = \" ${DIR_LIB_SRCS})\n\
# message(STATUS \"[ DIR_MAIN ] = \" ${DIR_MAIN})\n\
 \n\
# # 生成动态库 #\n\
# add_library(hello SHARED ${DIR_LIB_SRCS})\n\
# add_library(main SHARED ${DIR_MAIN})\n\
\n\
\n\
# # 生成静态库 和 动态库名称一样 #\n\
# # 生成静态库\n\
# add_library(hello_static STATIC ${DIR_LIB_SRCS}) \n\
\n\
# # 通过 set_target_properties 重新命名为libhello.a\n\
# set_target_properties(hello_static PROPERTIES OUTPUT_NAME \"hello\")\n\
# # 获取相关属性也是通过set_target_properties  OUTPUT_NAME静态库名字\n\
# # get_target_property(OUTPUT_VALUE hello_static OUTPUT_NAME)\n\
# # message(STATUS \"STATIC_LIB_OUTPUT_NAME = \" ${OUTPUT_VALUE})\n\
 \n\
# # 动态库版本号设置 , VERSION指代动态库版本，SOVERSION 指代 API 版本。\n\
# # 其中，libhello.so.1.2为动态库的文件名(realname)，libhello.so.1为动态库的别名(soname)，\n\
# # libhello.so为动态库的链接名（linkname）。\n\
# set_target_properties(hello PROPERTIES VERSION 1.2 SOVERSION 1)\n\
\n\
\n\
# # 清除 CMAKE_INSTALL_PREFIX 之前的缓存\n\
# unset(CMAKE_INSTALL_PREFIX CACHE)\n\
# # CMAKE_INSTALL_PREFIX默认值为：/usr/local\n\
# # 命令指定：cmake -DCMAKE_INSTALL_PREFIX=/home/ubuntu/test/usr\n\
# # 代码指定：\n\
# set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/usr)\n\
# message(STATUS \"[ install LIB--CMAKE_INSTALL_PREFIX ] = \" ${CMAKE_INSTALL_PREFIX})\n\
\n\
\n\
# # 安装共享库和头文件\n\
# # 将动态库和静态库安装到 ${CMAKE_INSTALL_PREFIX}/usr/lib\n\
# # bin lib 目录若是不存在则会创建该目录\n\
# INSTALL(TARGETS main hello hello_static #${PROJECT_NAME}_app\n\
# # RUNTIME DESTINATION bin\n\
# LIBRARY DESTINATION lib\n\
# ARCHIVE DESTINATION lib\n\
# )\n\
\n\
# # 安装头文件：将./src/hello.h ./src/main.h 文件安装到 ${CMAKE_INSTALL_PREFIX}/include\n\
# install(FILES ./src/hello.h ./src/main.h \n\
# DESTINATION include\n\
# )\n\
\n\
\n\
# # 安装目录：将src中的所有文件安装到 ${CMAKE_INSTALL_PREFIX}/src/doc目录下\n\
# install(DIRECTORY src/ DESTINATION src/doc)\n\
\n\
#########################################################################\n\
#                   需要编译子模块的CMakeLists.txt                       #\n\
#########################################################################\n\
# add_subdirectory(lib)\n";
    retdata.clear();
    retdata = strdata;
}



/*生成compile.sh*/
void gencompiledata(string &retdata)
{
    string strdata = "mkdir build\ncd build\ncmake ..\nmake";
    retdata.clear();
    retdata = strdata;
}