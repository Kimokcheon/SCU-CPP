# This page lists the useful opensource projects in C++
## [OpenCV](https://opencv.org/opencv-4-3-0/)

​	OpenCV (Open Source Computer Vision Library) is an open source computer vision and machine learning software library. The library has more than 2500 optimized algorithms, which includes a comprehensive set of both classic and state-of-the-art computer vision and machine learning algorithms. These algorithms can be used to detect and recognize faces, identify objects, classify human actions in videos, track camera movements, track moving objects, extract 3D models of objects, produce 3D point clouds from stereo cameras, stitch images together to produce a high resolution image of an entire scene, find similar images from an image database, etc.

```c++
// example
void Visualization::draw_single_line(cv::Mat& img, cv::Point2d start,
                                     cv::Point2d end, cv::Scalar scalar) {
  // width of line
  int thickness = 1;
  int lineType = cv::LineTypes::LINE_8;
  // draw the line between start and end
  cv::line(img, start, end, scalar, thickness, lineType);
}
```

## [protocol buffers](https://developers.google.com/protocol-buffers/docs/downloads)

​	Protocol buffers are Google's language-neutral, platform-neutral, extensible mechanism for serializing structured data – think XML, but smaller, faster, and simpler. You define how you want your data to be structured once, then you can use special generated source code to easily write and read your structured data to and from a variety of data streams and using a variety of languages.

```c++
// example
message Person {
  required string name = 1;
  required int32 id = 2;
  optional string email = 3;
}

Person john = Person.newBuilder()
    .setId(1234)
    .setName("John Doe")
    .setEmail("jdoe@example.com")
    .build();
output = new FileOutputStream(args[0]);
john.writeTo(output);

Person john;
fstream input(argv[1],
    ios::in | ios::binary);
john.ParseFromIstream(&input);
id = john.id();
name = john.name();
email = john.email();
```

## [kdtree](https://github.com/begeekmyfriend/kdtree)
### An open-source implementation of the KD tree data structure.

## CGAL

***computational geometry algorithms library***

*CGAL* is a software project that provides easy access to efficient and reliable geometric algorithms in the form of a C++ library. *CGAL* is used in various areas needing geometric computation, such as geographic information systems, computer aided design,
molecular biology, medical imaging,  computer graphics, and robotics.

## [dbg_macro](https://github.com/sharkdp/dbg-macro)

It provides a header with a `dbg` macro which makes printf-style debugging simpler.

## MyTinySTL

[MyTinySTL](https://github.com/Alinshans/MyTinySTL "github") is a tiny Standard Template Library based on C++11. It has a clear document and a simple test framework. It is not very difficult for beginners and you can implement your own STL.

## https://github.com/521xueweihan/HelloGitHub
### Opensource projects/books especially for the newbies

## LiquidFun

*1. Overview*   
**LiquidFun** is a 2D rigid-body and fluid simulation C++ library for games based upon Box2D.     
It provides support for procedural animation of physical bodies to make objects move and interact in realistic ways.
**LiquidFun source code** is available for download from **github.com/google/liquidfun**.  
*2. Purpose*  
It provides support for procedural animation of physical bodies to make objects move and interact in realistic ways.

## Qt
Qt is a useful framework to develop GUI programs, allowing programs to run perfectly in most platforms.

The core feature of Qt is signal/slot, which makes it easy and safe to interact between different modules.

## CGAL

A set of libraries providing easy access to geometric algorithms.

It gives dozens of demo codes in every single package and detailed tutorials, making it quick to start.

## Cocos2d-x

*Author*: Biru Yang     *Date* : 2020.6.23

Cocos2d-x是国内普及度较高的一款开源的**跨平台**移动2D游戏框架，其主要侧重于原生移动平台，适配iOS、Android、Windows、Mac等系统。其官网是这样描述这个框架的：

> 引擎提供了图形渲染、GUI、音频、网络、物理、用户输入等丰富的功能，被广泛应用于游戏开发及交互式应用的构建。

其核心部分用C++编写，支持用C++、Lua进行开发。

Cocos2d-x的用户既有小型的独立游戏工作室，也有如Zynga、Gamevil、Disney Mobile这样的知名公司。

其官网为：[Cocos2d-x](https://www.cocos.com/products#Cocos2d-x)

其在github上的页面为：[cocos2d-x_github](https://github.com/cocos2d/cocos2d-x)

## Lua

*Author*: Biru Yang     *Date* : 2020.6.23

Lua是一个**轻量级脚本语言**，由巴西里约热内卢天主教大学的一个三人研究小组于1993年开发。

它由**标准C**编成，可**通过灵活嵌入应用程序中从而为应用程序提供灵活的扩展和定制功能**，几乎在所有操作系统和平台上都能运行。

其主要优势如下：

+ **可扩展**：Lua脚本可以被C/C++调用，也可以调用C/C++的函数。
+ **轻量级**：其代码简洁，体积小、启动速度快。
+ 其它特性：同时支持**面向过程**和**函数式编程**。

由于其良好的可扩展性，许多知名应用和游戏（如 **魔兽世界**，**饥荒**）都将其作为嵌入式脚本语言。

其官网为[Lua官网](http://www.lua.org/)，在其上有对Lua特性的更全面、详尽的介绍，一个简明的入门手册，以及免下载的Lua体验页面。

## EasyX

EasyX is a graphic library for C++ that helps users get started with graphics and game programming quickly.
Official website: https://easyx.cn.

## SimpleNES https://github.com/amhndu/SimpleNES

This project provides a simple NES emulator written in C++. You can run some classic Nintendo games like SuperMarioBros with this NES.

I recommend this project because of both its simplicity and profundity. This project includes only less than 30 files, each of which has no more than 1000 lines of codes, which is very suitable for C++ beginners. Despite its simplicity, we can learn a lot about computer system architeture, which is really important for cs majors, including how CPU executes instructions, how the memory is allocated and so on.


## Google Test

### Overview
> Googletest is a testing framework developed by the Testing Technology team with Google’s specific requirements and constraints in mind. Whether you work on Linux, Windows, or a Mac, **if you write C++ code, googletest can help you. And it supports any kind of tests, not just unit tests**.

In addition to many internal projects at Google, GoogleTest is also used by [Chromium projects](http://www.chromium.org/), [LLVM](http://llvm.org/), [Protocol Buffers](https://github.com/google/protobuf), [OpenCV](http://opencv.org/).

The source code of **googletest** is available on [GitHub](https://github.com/google/googletest). As a beginner, it is advised to firstly refer to [Googletest Primer](https://google.github.io/googletest/primer.html) for basic concepts and usages, then [GoogleTest User’s Guide](https://google.github.io/googletest/) for a conprehensive guideline.

## CppJieba

结巴中文分词的Cpp版本，支持多种分词模式，将句子拆分成词以进行文本分析等应用。
https://github.com/yanyiwu/cppjieba


## Bitcoin 
Bitcoin is the largest cryptocurrency in the world. It is a decentralized currency and relies on peer-to-peer communications, meaning it has no authority and, being open-source, anyone can make edits. The name of the software bitcoin is built on is called "Bitcoin Core", and can be found here: https://github.com/bitcoin/bitcoin

## [https://github.com/vim-airline/vim-airline](https://github.com/vim-airline/vim-airline)

A good plugin for Vim which makes the line in the bottom of your vim look better.