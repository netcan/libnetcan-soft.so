NetCan-Soft >> libnetcan-soft.so使用说明
介绍:
    该库包含了一些实用的函数(后面具体说明)，我提供了动态库(libnetcan-soft.so)和静态库(libnetcan-soft.a)给大家使用。
    版本: V2.0.9
    下载地址: http://ncan.ys168.com
使用方法:
    如果你用到该库函数，这样编译你的代码:
        1.链接动态库libnetcan-soft.so (建议)
            # gcc -o [PROGRAM] [SOURCES] -lnetcan-soft.so
            # ldd [PROGRAM] (输出包含libnetcan-soft.so => [LIBDIR]则链接成功)
            # ./[PROGRAM] (运行程序)
        2.链接静态库libnetcan-soft.a
            # gcc -o [PROGRAM] [SOURCES] /lib/libnetcan-soft.a -lpthread
            # ldd [PROGRAM] (会发现没有libnetcan-soft.so了，但体积会大一点)
            # ./[PROGRAM] (运行程序)
函数介绍:
    注意: 该库所有函数执行成功会返回非0值，否则返回0值。
    文件操作:
        filebyte():
            原形: int filebyte( FILE * stream );
            功能: 计算文件 stream 大小并返回大小值(字节)            
        fline():
            原形: int fline( FILE * stream );
            功能: 计算文件 stream 行数并返回
        filearray():
            原形: int filearray( FILE * stream, char *array, int arraysize);
            功能: 把文件 stream 内容全复制到大小为 arraysize 的数组 array 中 
        ftotal():
            原形: int ftotal( DIR * path ); 
            功能: 计算目录 path 下的文件(目录)总数并返回
    其它:
        fcs():
            原形: char * fcs( char * title, char * path, int cs, char * out, int outsize);
            功能: 指定路径 path 让用户选择文件并输出文件名到大小为 outdir 的数组 out 中
            说明: 形参 title 为该函数的标题,默认为 "空(null)"
                  形参 path 为工作目录,默认为空,请赋值
                  形参 cs 为选择模式,有两个值 1/2,对应 单选/多选 ,默认为 多选(2)
                  该函数为指针函数,如果用户选择 "选定目录" 则返回该目录的地址值
                  如果用户选定了文件并按选择 "确定" 则返回该目录的地址值并输出用户选定的文件名到大小为 outsize 的数组 out 中,数组 out 中的文件名用字符 '/' 分开
                  如果用户选择 "返回" 将结束函数,返回值: "EXIT"
                  如果用户终止该函数,返回: "KILL"
            按键: 上下左右 控制,确定 执行,返回 切换菜单
                  配置文件(本地磁盘/NetCan-Soft/Settings/fcs_theme.conf)可自定义 按键/主题
        getch():
            原形: int getch(void);
            功能: 按下一个键并返回键值

下载/更新地址: http://ncan.ys168.com
QQ: 1469709759
