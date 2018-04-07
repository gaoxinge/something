# how python run

## process

```
     compile         optimize       interpret
.py ---------> .pyc ---------> .pyo ---------> result
```

## dll

```
   c compile          link
.c ---------> .obj ---------> .dll
```

### reference

- [cl创建并调用dll](http://blog.csdn.net/dreamcs/article/details/2497706)
- [ctypes — A foreign function library for Python](https://docs.python.org/2/library/ctypes.html)
- [浅谈Python程序和C程序的整合](https://www.ibm.com/developerworks/cn/linux/l-cn-pythonandc/)
- [Python外部函数调用库ctypes简介](http://python.jobbole.com/86940/)
- [Python通过ctypes调用C程序实例](http://python.jobbole.com/87242/)
- [使用ctypes进行Python和C的混合编程](https://www.cnblogs.com/gaowengang/p/7919219.html)
- [python ctypes探究----python与c的交互](https://www.cnblogs.com/night-ride-depart/p/4907613.html)

## pyd

```
   c compile
.c ---------> .pyd
```

### reference

- [学习笔记六：改善Python程序的91个建议](https://zhuanlan.zhihu.com/p/26761842)
- [error: Unable to find vcvarsall.bat](https://stackoverflow.com/questions/2817869/error-unable-to-find-vcvarsall-bat)
- [Python3.4用pip安装lxml时出现“Unable to find vcvarsall.bat”？](https://www.zhihu.com/question/26857761)
- [windows平台使用Microsoft Visual C++ Compiler for Python 2.7编译python扩展](https://www.cnblogs.com/lazyboy/p/4017567.html)
- [Windows下使用mingw32编译Python扩展py-bcrypt及使用patch文件备忘](http://wangye.org/blog/archives/737/)

## cython

```
       cython      c compile
.pyx ---------> .c ---------> .pyd
```

### reference

- [Cython: C-Extensions for Python](http://cython.org/)
- [Cython 基本用法](https://zhuanlan.zhihu.com/p/24311879)