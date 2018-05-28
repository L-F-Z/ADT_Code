#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<cstdarg>
#include<ctime>

//大写宏
#ifndef DBG_H_
    #define DBG_H_
#ifndef NDEBUG
    #define DEBUG

#define TRACK(x) (std::printf("track: " #x ":%d\n", x) * 0 + x)
//值追踪

#define CK(x) ({auto (_x)=(x);std::printf("track: " #x ":%d\n", _x);_x; })
//整数值追踪
//注意不要追踪会引发全局变化的函数和非整数值

#define CP (std::printf("Checkpoint. File:%s Line:%d\n",__FILE__, __LINE__))
//检查点

#define BP (std::printf("Breakpoint. File:%s Line:%d\n",__FILE__, __LINE__), getchar())
//断点
// #define LICENSE() (printf("Augustus Wang (c) 2017\n"),printf("Compiled on %s at %s\n", __DATE__,__TIME__))
//签名
#endif

#define L (std::printf("------------------------------ File:%s Line:%d\n", __FILE__, __LINE__))
//分割线

#define LICENSE (std::printf("\n%s\n", __FILE__), std::printf("Copyright (c) 2018 Augustus Wang (Wang Huaqiang) \n"), printf("Compiled on %s at %s\n\n", __DATE__, __TIME__))
//签名

#define GET(x) std::scanf("%d", &x)
//读取整数

#define LEN(x) (sizeof(x) / sizeof(x[0]))
//数组长度

#define M_MAX(x, y) (((x) > (y)) ? (x) : (y))
#define M_MIN(x, y) (((x) < (y)) ? (x) : (y))
//比较大小

//以下宏定义的临时变量隐藏在代码块中,只要你不用_开头命名变量就没有问题
#define MIN(x,y) ({\
    typeof(x) _x = (x);\
    typeof(y) _y = (y);\
    (void) (&_x == &_y);\
    _x < _y ? _x : _y; })\

#define MAX(x,y) ({\
    typeof(x) _x = (x);\
    typeof(y) _y = (y);\
    (void) (&_x == &_y);\
    _x > _y ? _x : _y; })\
//比较大小,且对于每个变量仅调用一次

#define RAW_CAT(X,Y) X##Y
//直接连接

#endif
