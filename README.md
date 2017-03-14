##桌面式三维扫描
---
>用于三维建模学习,机器视觉.
![meshlab查看](https://github.com/kintaiW/Scanner3D/raw/master/res/result.png)

###1. 环境
####1.1 软件环境
* __操作系统__: Ubuntu14.04.5
* __C/C++__: 默认
* __OpenCV__: 3.0
* __OpenGL__: 可选(需要做自制渲染)
* __Meshlab__: 用于查看生成的模型,安装简单

####1.2 硬件环境
* __线激光__: 标准规格,成本150RMB左右
* __转台__: 最好步进电机,一般的也可以,但需要做图片匹配
* __可拍照手机__:  
* __角尺__: 量出相机光心与线激光夹角,追求精度另说

###2. 编译
在src文件夹下
* __$__:make
* __model.ply__: 运行后生成的ply格式模型
![meshlab查看](https://github.com/kintaiW/Scanner3D/raw/master/res/out.png)

###3. 原理
* __[原理图](http://blog.sina.com.cn/s/blog_662c78590100zqwd.html)__
* __[开源项目](https://github.com/bqlabs/horus)__

###4. 源码结构
coming soon
