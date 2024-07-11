# version 1.0.0
# 1、使用方法
1

# 参数说明
-c ： 生成C语言.h和.c文件,使用该参数后面跟需要生成文件的名称,例如： cw-widget-cpp -c ctest
-n ： 生成C++的.h和.c文件,使用该参数后面跟需要生成文件的名称,例如： cw-widget-cpp -n cpptest
-p ： 生成工程,使用该参数后面跟需要生成工程的名称,例如： cw-widget-cpp -p testproject 或 cw-widget-cpp -p testproject -c ctest
pth : 生成linux c pthread 的api测试文件,例如： cw-widget-cpp pth
path : 获取当前工作路径下 ".h .c .cpp"文件的绝对路径, 例如： cw-widget-cpp path
# 使用命令
# 注：所有生成物都在当前终端工作路径下：

# 例如：
# 生成C语言文件 文件名字：main
cw-widget-cpp

# 生成C语言文件 文件名字：ctest
cw-widget-cpp -c ctest

# 生成C++语言文件 文件名字：cpptest
cw-widget-cpp -n cpptest

# 生成C语言工程，工程名字：testproject 文件名字：main
cw-widget-cpp -p testproject

# 生成C语言工程，工程名字：testproject 文件名字：ctest
cw-widget-cpp -p testproject -c ctest

# 生成C++工程，工程名字：testproject 文件名字：cpptest
cw-widget-cpp -p testproject -n cpptest

# 生成linux c pthread 的api测试文件
cw-widget-cpp pth

# 获取当前工作路径下 ".h .c .cpp"文件的绝对路径
cw-widget-cpp path


## 编译命令
./compile.sh


# bug:


# modify


# 需要新增功能
1、生成linux c和通用C语言的读取文件和写入文件代码

