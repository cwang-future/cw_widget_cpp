
#include "gen_thread_code.h"

static const char *cthread_code = "\n\
#include <stdio.h>\n\
#include <pthread.h>\n\
#include <string.h>\n\
#include <unistd.h>\n\
\n\
\n\
/*动态库名称: pthread */\n\
\n\
int itest = 0;\
\n\
/*静态初始化 锁*/\n\
//static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;\n\
/*\n\
使用锁的注意事项：\n\
    1、锁的粒度越小越好\n\
    2、防止死锁\n\
*/\n\
pthread_mutex_t lock_itest;\n\
\n\
/*线程回调函数*/\n\
void *thread_cb(void *udata);\n\
\n\
void *thread_cb(void *udata)\n\
{\n\
    printf(\"child thread : %s\\n\", (char *)udata);\n\
    sleep(2);\n\
    pthread_mutex_lock(&lock_itest);\n\
    itest = 4;\n\
    pthread_mutex_unlock(&lock_itest);\n\
\n\
    /*使线程结束，并将udata作为返回值返回*/\n\
    pthread_exit((void *)udata);\n\
    //or\n\
    //return udata;\n\
}\n\
\n\
void run_thread()\n\
{\n\
    pthread_t tid;\n\
    int ret;\n\
    char *ret_thread = NULL;\n\
    char *chello = \"hello world!\";\n\
    /*动态初始化锁*/\n\
    pthread_mutex_init(&lock_itest, NULL);\n\
\n\
    /*创建线程*/\n\
    if((ret = pthread_create(&tid, NULL, thread_cb, (void *)chello)) != 0)\n\
    {\n\
        printf(\"pthread_create error : %s\\n\", strerror(ret)); /*#include <string.h>*/\n\
        return;\n\
    }\n\
    /*pthread_detach(tid);  //设置线程自动分离,退出后,无系统残留资源*/\n\
    /*阻塞等待线程退出*/\n\
    pthread_join(tid, (void**)&ret_thread);\n\
    printf(\"main thread ID : %ld  child thread return value: %s\\n\", pthread_self(),ret_thread);\n\
    /*销毁锁*/\n\
    pthread_mutex_destroy(&lock_itest);\n\
}\n\
\n\
#if 0\n\
其他线程函数分析：\n\
/////////////////////////////////\n\
pthread_cancel函数\n\
/////////////////////////////////\n\
函数作用：\n\
杀死(取消)线程。\n\
头文件：\n\
#include <pthread.h>\n\
函数原型：\n\
int pthread_cancel(pthread_t thread);\n\
函数参数：\n\
thread：线程ID。\n\
返回值：\n\
成功：0；\n\
失败：错误号。\n\
注意：\n\
可通过pthread_testcancel()函数设置一个取消点。\n\
取消点：是线程检查是否被取消，并按请求进行动作的一个位置。\n\
    通常是一些系统调用creat，open，pause，close，read，write..... 执行命令man 7 pthreads可以查看具备这些取消点的系统调用列表。也可参阅 APUE.12.7 取消选项小节。\n\
\n\
/////////////////////////////////\n\
pthread_equal 函数\n\
/////////////////////////////////\n\
函数作用：\n\
比较两个线程ID是否相等。\n\
头文件：\n\
#include <pthread.h>\n\
函数原型：\n\
int pthread_equal(pthread_t t1, pthread_t t2);\n\
函数参数：\n\
t1：需要比较的线程号1；\n\
t2：需要比较的线程号2；\n\
返回值：\n\
返回非0：两个线程相等。\n\
返回0：表示其他。\n\
\n\
#endif\n\
\n\
int main(int argc, char **argv)\n\
{\n\
    run_thread();\n\
    printf(\"run_thread.\\n\");\n\
    return 0;\n\
}";

void gen_thread_code(string &thread_code)
{
    thread_code = cthread_code;
}
