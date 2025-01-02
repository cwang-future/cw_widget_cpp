#########################################################################
#版本名称
cmake_minimum_required(VERSION 3.10.2)
#工程名
project(cw-widget-cpp)
#########################################################################

#########################################################################
# 编译代码检查命令选项
#########################################################################
#ADD_DEFINITIONS ：给gcc添加命令选项
#-Os：相当于-O2.5。是使用了所有-O2的优化选项，但又不缩减代码尺寸的方法。
#-Wall：打开所有警告
#-Werror：将所有的警告转变为错误
#-Wno-poison-system-directories：交叉编译时使用-I/usr/include等选项的警告可以使用新选项“-Wno poison system directories”禁用
#--std=gnu99：使用gnu99来编译，对C++无效
#-Wmissing-prototypes: 检查未声明的函数原型。
#-Wmissing-declarations: 检查未声明的全局变量。
# ADD_DEFINITIONS(-Os -Wall -Werror -Wmissing-declarations)


#########################################################################
#                           生成 可执行程序                              #
#########################################################################

# 设置可执行程序的生成目录 #
#EXECUTABLE_OUTPUT_PATH ：需要存放的可执行程序的位置，为cmake变量
#PROJECT_SOURCE_DIR：根目录所在路径变量，为cmake变量
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#打印EXECUTABLE_OUTPUT_PATH的值
message(STATUS "[ EXECUTABLE_OUTPUT_PATH ] = ${EXECUTABLE_OUTPUT_PATH}")

###################
# 设置需要的头文件 #
###################
# # 清除 INCLUDE_DIR 之前的缓存
# unset(INCLUDE_DIR CACHE)
# # 在指定路径下查找 test.h
# FIND_PATH(INCLUDE_DIR       
#     # 虽然有多条路径，但只会把含当前头文件的目录加入到 INCLUDE_DIR 中
#     NAMES test.h HINTS ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/src/test
# )
# message("[ INCLUDE_DIR ] = ${INCLUDE_DIR}")
# 设置头文件
INCLUDE_DIRECTORIES(
    # ${INCLUDE_DIR}
    ./src
	./src/gen
	./src/tool
)

#########################
# 设置需要编译的源码文件 #
#########################
#源码存放的顶层位置文件名称
set(SRC_PATH  "src")

# 设置${PROJECT_NAME}_app可执行程序需要的源码
#将${SRC_PATH}/*.c中的.c文件赋给ALL_SRC变量
file(GLOB_RECURSE ALL_SRC "${SRC_PATH}/*.cpp" "${SRC_PATH}/*.c")

#设置${PROJECT_NAME}_server_app可执行程序的需要的源码
set(COMPILE_SRC  ${ALL_SRC})
#假设你有不需要编译的源文件，找到该可执行文件不需要的源文件
# file(GLOB_RECURSE Exclude_C_SRC  
# "${SRC_PATH}/main2.c" 
#  ${SRC_PATH}/test2/*.c 
# )
#在COMPILE_SRC排除该可执行文件不需要的源文件
# list(REMOVE_ITEM   COMPILE_SRC   ${Exclude_C_SRC} )
message(STATUS "[ COMPILE_SRC ] = " ${COMPILE_SRC})


#################
# 生成可执行程序 #
#################
#生成${PROJECT_NAME}_app 程序
add_executable(${PROJECT_NAME} ${COMPILE_SRC})



###########################
# 添加 可执行程序 的依赖库 #
###########################
#例如：你需要添加查 ubox ubus blobmsg_json库
#查找库
# find_library(UBOX_LIBRARY NAMES ubox	HINTS /usr/local/lib)	
# find_library(UBUS_LIBRARY NAMES ubus	HINTS /usr/local/lib)
# find_library(BLOBMSG_JSON_LIBRARY NAMES blobmsg_json	HINTS /usr/local/lib)

# message(STATUS "[ UBOX_LIBRARY ] = ${UBOX_LIBRARY}")
# message(STATUS "[ UBUS_LIBRARY ] = ${UBUS_LIBRARY}")
# message(STATUS "[ BLOBMSG_JSON_LIBRARY ] = ${BLOBMSG_JSON_LIBRARY}")

#设置可执行文件需要依赖的库
target_link_libraries(${PROJECT_NAME}
    # ${UBOX_LIBRARY}
    # ${UBUS_LIBRARY}
    # ${BLOBMSG_JSON_LIBRARY}
)

########################
#安装 可执行程序 到系统 #
########################
# 清除 CMAKE_INSTALL_PREFIX 之前的缓存
# unset(CMAKE_INSTALL_PREFIX CACHE)
# CMAKE_INSTALL_PREFIX默认值为：/usr/local
# 命令指定：cmake -DCMAKE_INSTALL_PREFIX=/home/ubuntu/test/usr
# 代码指定：
# set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/usr)
message(STATUS "[ install BIN--CMAKE_INSTALL_PREFIX ] = " ${CMAKE_INSTALL_PREFIX})
INSTALL(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
