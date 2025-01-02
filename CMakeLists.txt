########################################################################
# 版本名称
cmake_minimum_required(VERSION 3.10.2)
# 工程名
project(cw-widget-cpp)
#########################################################################


#########################################################################
# 编译代码检查命令选项
#########################################################################
# ADD_DEFINITIONS ：给gcc添加命令选项
# -Os：相当于-O2.5。是使用了所有-O2的优化选项，但又不缩减代码尺寸的方法。
# -Wall：打开所有警告
# -Werror：将所有的警告转变为错误
# -Wno-poison-system-directories：交叉编译时使用-I/usr/include等选项的警告可以使用新选项“-Wno poison system directories”禁用
# --std=gnu99：使用gnu99来编译，对C++无效
# -Wmissing-prototypes: 检查未声明的函数原型。
# -Wmissing-declarations: 检查未声明的全局变量。
# ADD_DEFINITIONS(-Os -Wall -Werror -Wmissing-declarations)

#########################################################################
#                           生成 可执行程序                              #
#########################################################################

# 设置可执行程序的生成目录 #
# EXECUTABLE_OUTPUT_PATH ：需要存放的可执行程序的位置，为cmake变量
# PROJECT_SOURCE_DIR：根目录所在路径变量，为cmake变量
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# 打印EXECUTABLE_OUTPUT_PATH的值
MESSAGE(STATUS "[ EXECUTABLE_OUTPUT_PATH ] = ${EXECUTABLE_OUTPUT_PATH}")

#################
# 设置代码外部宏 #
#################
# 例如：
# SET(HELLO_WORLD "hello world")
# SET(TEST_MAX_NUM 1048576)
# ADD_DEFINITIONS( -DHELLO_WORLD="${HELLO_WORLD}")
# ADD_DEFINITIONS( -DTEST_MAX_NUM=${TEST_MAX_NUM})

###################
# 设置需要的头文件 #
###################
# # 清除 INCLUDE_DIR 之前的缓存
# UNSET(INCLUDE_DIR CACHE)
# # 在指定路径下查找 test.h
# FIND_PATH(INCLUDE_DIR    
#     # 虽然有多条路径，但只会把含当前头文件的目录加入到 INCLUDE_DIR 中
#     NAMES test.h HINTS ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/src/test
# )
# MESSAGE("[ INCLUDE_DIR ] = ${INCLUDE_DIR}")
# # 设置头文件
INCLUDE_DIRECTORIES(
    # ${INCLUDE_DIR}
	./src
	./src/gen
	./src/tool
)

#########################
# 设置需要编译的源码文件 #
#########################
# 源码存放的顶层位置文件名称
SET(SRC_PATH  "src")

# 设置${PROJECT_NAME}_app可执行程序需要的源码
# 将${SRC_PATH}/*.c中的.c文件赋给ALL_SRC变量
FILE(GLOB_RECURSE ALL_SRC  "${SRC_PATH}/*.c" "${SRC_PATH}/*.cpp")

# 设置${PROJECT_NAME}_server_app可执行程序的需要的源码
SET(COMPILE_SRC  ${ALL_SRC})
# 假设你有不需要编译的源文件，找到该可执行文件不需要的源文件
# FILE(GLOB_RECURSE Exclude_C_SRC  
# "${SRC_PATH}/main2.c" 
#  ${SRC_PATH}/test2/*.c 
# )
# 在COMPILE_SRC排除该可执行文件不需要的源文件
# LIST(REMOVE_ITEM   COMPILE_SRC   ${Exclude_C_SRC} )
MESSAGE(STATUS "[ COMPILE_SRC ] = " ${COMPILE_SRC})


#################
# 生成可执行程序 #
#################
# 生成${PROJECT_NAME}_app 程序
ADD_EXECUTABLE(${PROJECT_NAME} ${COMPILE_SRC})


###########################
# 添加 可执行程序 的依赖库 #
###########################
# 例如：你需要添加查 ubox ubus blobmsg_json库
# 查找库
# FIND_LIBRARY(UBOX_LIBRARY NAMES ubox	HINTS /usr/local/lib)
# FIND_LIBRARY(UBUS_LIBRARY NAMES ubus	HINTS /usr/local/lib)
# FIND_LIBRARY(BLOBMSG_JSON_LIBRARY NAMES blobmsg_json	HINTS /usr/local/lib)

# MESSAGE(STATUS "[ UBOX_LIBRARY ] = ${UBOX_LIBRARY}")
# MESSAGE(STATUS "[ UBUS_LIBRARY ] = ${UBUS_LIBRARY}")
# MESSAGE(STATUS "[ BLOBMSG_JSON_LIBRARY ] = ${BLOBMSG_JSON_LIBRARY}")

# 设置可执行文件需要依赖的库
TARGET_LINK_LIBRARIES(${PROJECT_NAME}
    # ${UBOX_LIBRARY}
    # ${UBUS_LIBRARY}
    # ${BLOBMSG_JSON_LIBRARY}
)

########################
# 安装 可执行程序 到系统 #
########################
# 清除 CMAKE_INSTALL_PREFIX 之前的缓存
# UNSET(CMAKE_INSTALL_PREFIX CACHE)
# CMAKE_INSTALL_PREFIX默认值为：/usr/local
# 命令指定：cmake -DCMAKE_INSTALL_PREFIX=/home/ubuntu/test/usr
# 代码指定：
# SET(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/usr)
# MESSAGE(STATUS "[ install BIN--CMAKE_INSTALL_PREFIX ] = " ${CMAKE_INSTALL_PREFIX})
# INSTALL(TARGETS ${PROJECT_NAME}_app RUNTIME DESTINATION bin)


#########################################################################
#                               生成 lib 库                             #
#########################################################################

################### 例子：#####################

# #LIBRARY_OUTPUT_PATH ：需要存放的库的位置，为cmake变量
# SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# 把所有源文件添加到列表
# AUX_SOURCE_DIRECTORY(. DIR_LIB_SRCS)
# 设置单个文件
# SET(DIR_LIB_SRCS ./src/hello.c)
# SET(DIR_MAIN ./src/main.c)

# MESSAGE(STATUS "[ DIR_LIB_SRCS ] = " ${DIR_LIB_SRCS})
# MESSAGE(STATUS "[ DIR_MAIN ] = " ${DIR_MAIN})
 
# # 生成动态库 #
# ADD_LIBRARY(hello SHARED ${DIR_LIB_SRCS})
# ADD_LIBRARY(main SHARED ${DIR_MAIN})


# # 生成静态库 和 动态库名称一样 #
# # 生成静态库
# ADD_LIBRARY(hello_static STATIC ${DIR_LIB_SRCS}) 

# 通过 SET_TARGET_PROPERTIES 重新命名为libhello.a
# SET_TARGET_PROPERTIES(hello_static PROPERTIES OUTPUT_NAME "hello")
# 获取相关属性也是通过 SET_TARGET_PROPERTIES  OUTPUT_NAME静态库名字
# GET_TARGET_PROPERTY(OUTPUT_VALUE hello_static OUTPUT_NAME)
# MESSAGE(STATUS "STATIC_LIB_OUTPUT_NAME = " ${OUTPUT_VALUE})
 
# 动态库版本号设置 , VERSION指代动态库版本，SOVERSION 指代 API 版本。
# 其中，libhello.so.1.2为动态库的文件名(realname)，libhello.so.1为动态库的别名(soname)，
# libhello.so为动态库的链接名（linkname）。
# SET_TARGET_PROPERTIES(hello PROPERTIES VERSION 1.2 SOVERSION 1)


# 清除 CMAKE_INSTALL_PREFIX 之前的缓存
# UNSET(CMAKE_INSTALL_PREFIX CACHE)
# CMAKE_INSTALL_PREFIX默认值为：/usr/local
# 命令指定：cmake -DCMAKE_INSTALL_PREFIX=/home/ubuntu/test/usr
# 代码指定：
# SET(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/usr)
# MESSAGE(STATUS "[ install LIB--CMAKE_INSTALL_PREFIX ] = " ${CMAKE_INSTALL_PREFIX})


# 安装共享库和头文件
# 将动态库和静态库安装到 ${CMAKE_INSTALL_PREFIX}/usr/lib
# bin lib 目录若是不存在则会创建该目录
# INSTALL(TARGETS main hello hello_static #${PROJECT_NAME}_app
# RUNTIME DESTINATION bin
# LIBRARY DESTINATION lib
# ARCHIVE DESTINATION lib
# )

# # 安装头文件：将./src/hello.h ./src/main.h 文件安装到 ${CMAKE_INSTALL_PREFIX}/include
# INSTALL(FILES ./src/hello.h ./src/main.h 
# DESTINATION include
# )


# # 安装目录：将src中的所有文件安装到 ${CMAKE_INSTALL_PREFIX}/src/doc目录下
# INSTALL(DIRECTORY src/ DESTINATION src/doc)

#########################################################################
#                   需要编译子模块的CMakeLists.txt                       #
#########################################################################
# ADD_SUBDIRECTORY(lib)
