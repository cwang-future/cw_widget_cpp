#########################################################################
#版本名称
cmake_minimum_required(VERSION 3.10.2)
#工程名
project(ubus-learn)
#########################################################################


#########################################################################
#                           生成 可执行程序                              #
#########################################################################

# 设置可执行程序的生成目录 #
#EXECUTABLE_OUTPUT_PATH ：需要存放的可执行程序的位置，为cmake变量
#PROJECT_SOURCE_DIR：根目录所在路径变量，为cmake变量
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#打印EXECUTABLE_OUTPUT_PATH的值
message(STATUS "[ EXECUTABLE_OUTPUT_PATH ] = ${EXECUTABLE_OUTPUT_PATH}")

#################
# 设置代码外部宏 #
#################
#例如：
# SET(HELLO_WORLD "hello world")
# SET(TEST_MAX_NUM 1048576)
# ADD_DEFINITIONS( -DHELLO_WORLD="${HELLO_WORLD}")
# ADD_DEFINITIONS( -DTEST_MAX_NUM=${TEST_MAX_NUM})

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
# # 设置头文件
# INCLUDE_DIRECTORIES
# (
#     ${INCLUDE_DIR}
# )

#########################
# 设置需要编译的源码文件 #
#########################
#源码存放的顶层位置文件名称
set(SRC_PATH  "src")

# 设置${PROJECT_NAME}_app可执行程序需要的源码
#将${SRC_PATH}/*.c中的.c文件赋给ALL_SRC变量
file(GLOB_RECURSE ALL_SRC  "${SRC_PATH}/*.c" "${SRC_PATH}/*.cpp")

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
add_executable(${PROJECT_NAME}_app ${COMPILE_SRC})



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
target_link_libraries(${PROJECT_NAME}_app
    # ${UBOX_LIBRARY}
    # ${UBUS_LIBRARY}
    # ${BLOBMSG_JSON_LIBRARY}
)

########################
#安装 可执行程序 到系统 #
########################
# 清除 CMAKE_INSTALL_PREFIX 之前的缓存
unset(CMAKE_INSTALL_PREFIX CACHE)
# CMAKE_INSTALL_PREFIX默认值为：/usr/local
# 命令指定：cmake -DCMAKE_INSTALL_PREFIX=/home/ubuntu/test/usr
# 代码指定：
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/usr)
message(STATUS "[ BIN--CMAKE_INSTALL_PREFIX ] = " ${CMAKE_INSTALL_PREFIX})
INSTALL(TARGETS ${PROJECT_NAME}_app
   RUNTIME DESTINATION bin
)


#########################################################################
#                               生成 lib 库                             #
#########################################################################

################### 例子：#####################

# #LIBRARY_OUTPUT_PATH ：需要存放的库的位置，为cmake变量
# set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# # 把所有源文件添加到列表
# # aux_source_directory(. DIR_LIB_SRCS)
# # 设置单个文件
# set(DIR_LIB_SRCS ./src/hello.c)
# set(DIR_MAIN ./src/main.c)

# message(STATUS "[ DIR_LIB_SRCS ] = " ${DIR_LIB_SRCS})
# message(STATUS "[ DIR_MAIN ] = " ${DIR_MAIN})
 
# # 生成动态库
# add_library(hello SHARED ${DIR_LIB_SRCS})
# add_library(main SHARED ${DIR_MAIN})


# # 生成静态库 和 动态库名称一样
# # 生成静态库
# add_library(hello_static STATIC ${DIR_LIB_SRCS}) 

# # 通过 set_target_properties 重新命名为libhello.a
# set_target_properties(hello_static PROPERTIES OUTPUT_NAME "hello")
# # 获取相关属性也是通过set_target_properties  OUTPUT_NAME静态库名字
# # get_target_property(OUTPUT_VALUE hello_static OUTPUT_NAME)
# # message(STATUS "STATIC_LIB_OUTPUT_NAME = " ${OUTPUT_VALUE})
 
# # 动态库版本号设置 , VERSION指代动态库版本，SOVERSION 指代 API 版本。
# # 其中，libhello.so.1.2为动态库的文件名(realname)，libhello.so.1为动态库的别名(soname)，
# # libhello.so为动态库的链接名（linkname）。
# set_target_properties(hello PROPERTIES VERSION 1.2 SOVERSION 1)


# # 清除 CMAKE_INSTALL_PREFIX 之前的缓存
# unset(CMAKE_INSTALL_PREFIX CACHE)
# # CMAKE_INSTALL_PREFIX默认值为：/usr/local
# # 命令指定：cmake -DCMAKE_INSTALL_PREFIX=/home/ubuntu/test/usr
# # 代码指定：
# set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/usr)
# message(STATUS "[ LIB--CMAKE_INSTALL_PREFIX ] = " ${CMAKE_INSTALL_PREFIX})
 

# # 安装共享库和头文件
# # 将动态库和静态库安装到 ${CMAKE_INSTALL_PREFIX}/usr/lib
# # bin lib 目录若是不存在则会创建该目录
# INSTALL(TARGETS main hello hello_static #${PROJECT_NAME}_app
# # RUNTIME DESTINATION bin
# LIBRARY DESTINATION lib
# ARCHIVE DESTINATION lib
# )

# # 安装头文件：将./src/hello.h ./src/main.h 文件安装到 ${CMAKE_INSTALL_PREFIX}/include
# install(FILES ./src/hello.h ./src/main.h 
# DESTINATION include
# )

 
# # 安装目录：将src中的所有文件安装到 ${CMAKE_INSTALL_PREFIX}/src/doc目录下
# install(DIRECTORY src/ DESTINATION src/doc)

#########################################################################
#                   需要编译子模块的CMakeLists.txt                       #
#########################################################################
# add_subdirectory(lib)

