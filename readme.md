## 简介

20240110 Bistu 《 Soft Design 》

ex1: 点、线、圆、矩形、抛物线的类定义; 

ex2: BMP彩色转灰色; 

ex3: opencv实现直线和圆检测;

ex4：AD5935 板卡驱动;

## 环境

win10_22H2

vs2019

vcpkg 包管理器内   --->  安装: opencv:x64-windows

opencv版本：4.8.0

WindowsSDK版本： 10.0.19041.0

MSVC版本（vc16)： 14.29.30133



## 文件结构：

experiments.sln   (vs2019解决方案，用vs2019打开)

/ex1

/ex2

/ex3

/ex4







## 说明

* 所有实验都让 vs2019 与 vcpkg 绑定，不然无法导入 opencv

* 所有实验的 Include 目录需与你电脑的开发环境的库目录一致。

* ex4 需包含库目录：

​				D:\Program Files (x86)\ART\USB5935\Driver\INF\Win32&Win64

​				D:\Program Files (x86)\ART\USB5935\Driver\INF\Win32&Win64\amd64