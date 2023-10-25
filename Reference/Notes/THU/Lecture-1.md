# Lecture 1

## Command-line argument（命令行参数）

#### 1. Suppose that you want to write an A+B program that obtains A and B from command-line arguments. How can we do this? Please give an example of the source code, as well as how to compile and run the program.

```cpp
//a.cpp
#include <iostream> 
#include <cstdlib> 
#include <cstdio> 
int main(int argc, char** argv)
{
	std::cout << atof(argv[1]) + atof(argv[2]) << std::endl;
	return 0;
}
```

- Windows:
 - To compile：`g++ a.cpp -o a.exe`
 - To run：`a.exe 1 2`
- Ubuntu:
 - To compile: `g++ a.cpp -o a`
 - To run: `./a 1 2`
	
#### 2. Please list（列举）the potential advantages and disadvantages of obtaining arguments by file reading vs. by command-line argument.

- Advantage of file reading:
  - File reading can be used in programs with a GUI.
  - Files can be copied and modified easily.
  - Files can provide a larger size of arguments.
  - When reading large amounts of arguments(>= 10000), file reading is more convenient than command-line argument.
  - Files can be saved, thus provide an easier way to analyse data. 
- Disadvantage of file reading:
  - File IO is more complex and slower than command arguments with exceptions to handle.
  - Not easy to know argument amounts.
- Advantage of command-line argument:
  - Makes the program easier to be called in command-line.
  - Makes the program callable in batch scripts for tasks like parameter sweeping (参数扫描, 以不同的参数运行同一个程序).
- Diadvantage of command-line argument:
  - Unable to handle large number of arguments.
  - Takes efforts to parse data from `argc` and `argv`.

#### 3. How do you input a command-line argument with spaces in it? For example, how can we input ‘Hello World’ as a single argument?

- Use quotation marks (`""`) to embrace the whole message. For example, to input 'Hello World' as one argument, put `"Hello World"` in the command-line, or input a slash sign '`\`' before the space (`Hello\ World`):
  - `a.exe "Hello World"`
  - `a.exe Hello\ World`

#### 4. What is the meaning of argc and argv? What are their data types? If the command “a.exe 1 2 3” is executed in the terminal (终端), what are the values of argc and argv?

- `argc`: the number of arguments obtained from the terminal. The data type of `argc` is `int`.
- `argv`: the arguments obtained from the terminal. The data type of `argv` is `char**`, i.e., an array of `char*`.
- When "`a.exe 1 2 3`" is executed in the terminal, `argc = 4`, and `argv = {"a.exe", "1", "2", "3"}`

## Translation（翻译）from source code（源代码）to binary executable（二进制可执行文件）

#### 5.	Please explain how interpreters（解释器）and compilers（编译器）work. What are the typical programming languages (典型编程语言) for each of the two translation methods? Please list the advantages and disadvantages of interpreters vs. compilers.

- Interpreters translate the code line-by-line while executing the program. So, in general, interpreters run programs slower than compilers. The most common examples of interpreted languages are Python and java.
- Advantages: programs can be easily transplanted (移植) to other platforms (平台), because the execution of the program only relies on the interpreters.
- Disadvantage: run slower than compiled program. They also use more memory.
- Compilers compile the program into machine code, which is saved as a binary file (二进制文件). Then the machine code runs directly on the operating system (操作系统). This makes running compilers faster than running interpreters. The most common examples of compiled languages are C and C++.
- Advantages: faster than interpreters. The compiler can also perform code optimization during the compiling process.
- Disadvantage: For different platforms, the source code needs to be recompiled (重新编译).

#### 6.	The g++ compiler is universally used in both commercial and scientific research projects. So you are supposed to know how to use g++ to compile C++ source files into the binary file. State the basic usage (基本用法) on how to compile a source file. List useful compiling options (编译选项) as many as possible, and explain why and when do we need these options.

```plain
Usage: g++ [options] file...
Options:

  -c                            Compile and assemble, but do not link
  -o < file>                    Place the output into <file>
  -shared                       Create a shared library
  --help                        Display this information
  --version                     Display compiler version information
  -print-search-dirs            Display the directories in the compiler's search path
  -pass-exit-codes              Exit with highest error code from a phase
  --target-help                 Display target specific command line options
  --help                        Display specific types of command line options (Use '-v --help' to display command line options of sub-processes)
  -dumpspecs                    Display all of the built in spec strings
  -dumpversion                  Display the version of the compiler
  -dumpmachine                  Display the compiler's target processor
  -print-libgcc-file-name       Display the name of the compiler's companion library
  -print-file-name=< lib>       Display the full path to library <lib>
  -print-prog-name=< prog>      Display the full path to compiler component <prog>
  -print-multiarch              Display the target's normalized GNU triplet, used as a component in the library path
  -print-multi-directory        Display the root directory for versions of libgcc
  -print-multi-lib              Display the mapping between command line options and multiple library search directories
  -print-multi-os-directory     Display the relative path to OS libraries
  -print-sysroot                Display the target libraries directory
  -print-sysroot-headers-suffix Display the sysroot suffix used to find headers
  -Wa,< options>                Pass comma-separated <options> on to the assembler
  -Wp,< options>                Pass comma-separated <options> on to the preprocessor
  -Wl,< options>                Pass comma-separated <options> on to the linker
  -Xassembler <arg>            Pass <arg> on to the assembler
  -Xpreprocessor <arg>         Pass <arg> on to the preprocessor
  -Xlinker <arg>               Pass <arg> on to the linker
  -save-temps                   Do not delete intermediate files
  -save-temps=<arg>            Do not delete intermediate files
  -no-canonical-prefixes        Do not canonicalize paths when building relative prefixes to other gcc components
  -pipe                         Use pipes rather than intermediate files
  -time                         Time the execution of each subprocess
  -specs=<file>                Override built-in specs with the contents of <file>
  -std=<standard>              Assume that the input sources are for <standard>
  --sysroot=<directory>        Use <directory> as the root directory for headers and libraries
  -B <directory>               Add <directory> to the compiler's search paths
  -v                            Display the programs invoked by the compiler
  -###                          Like -v but options quoted and commands not executed
  -E                            Preprocess only; do not compile, assemble or link
  -S                            Compile only; do not assemble or link
  -pie                          Create a position independent executable
  -x < language>                Specify the language of the following input files
                                Permissible languages include: c c++ assembler none
                                'none' means revert to the default behavior of
                                guessing the language based on the file's extension

```

Options starting with `-g`, `-f`, `-m`, `-O`, `-W`, or `--param` are automatically passed to the various sub-processes invoked by `g++`. In order to pass other options on to these processes the `-W<letter>` options must be used.

#### 7.	What is a C/C++ library (库)? On Linux, how do we build a library using the g++ compiler? How do we use an existing library with the g++ compiler? At what stage is a library loaded (载入)? Is it always during the linking stage (链接阶段)? Please explain the difference between static (静态) and dynamic (动态) libraries.

* C/C++ libraries are modules of already-compiled objective code. By libraries, we could reuse functions/classes provided by others.
* A library can be used by including the related header files and linking the library (`*.a` or `*.lib`). 
* There are two types of libraries, i.e., *static* library and *dynamic* library.
* To build a static library with `g++`, run the following commands:
  ```bash
  g++ -c lib1.cpp -o lib1.o
  g++ -c lib2.cpp -o lib2.o
  ar -rv lib.a lib1.o lib2.o
  ranlib lib.a
  ``` 
* To link the static library `lib.a`, run:
  ```bash
  g++ main.o lib.a –o main.exe
  ```
* Static libraries are loaded during the compiling process. Whereas dynamic libraries are loaded during the execution of the program, when the function in the library is being called.
* A static library is required only at compile time. It is not needed during execution of the program, because all the functions in the library have been compiled into the executable. However, a dynamic library is required at runtime rather than at compile time, because the functions in the library are not compiled into the executable. Therefore, the executable with static library is larger in size than the one with dynamic library. 


## Multi-file project

#### 8.	On Linux, assuming a project contains the files main.cpp, sum.cpp, product.cpp, and functions.h, please write the command(s) needed to compile them into test with g++.

```bash
g++ -c main.cpp -o main.o
g++ -c sum.cpp -o sum.o
g++ -c product.cpp -o product.o
g++ main.o sum.o product.o -o test
```

#### 9.	Please explain why multiple files are necessary for a project. What are the advantages of multi-file project compared with single-file project?

- A large project often needs a lot of developers. It is error-prone for all the developers to modify a single file simultaneously.
- For a large project, the compilation process usaully takes a long time. Using multi-file projects, we can compile only the modified file (using `makefile` to take care of the compilation process), whereas in a single-file project, even a slight change in the file will cause the whole program to be re-compiled, which is very time-consuming.

#### 10. What is separate compilation (分段编译)? Why is it better than direct compilation, i.e., to generate the executable directly from the source files? Please state the whole process of separate compilation.

- Different source files (`.cpp`) (源文件) are compiled separately into different object files (`.o` or `.obj`) (目标文件). E.g., "`g++ -c fun.cpp -o fun.o`"
- The object files are then combined into the final executable program (可执行程序) (default name is `a.exe` or `a.out`) by a tool called linker (链接器)
- Advantage of separate compilation: separate the whole compiling process into different steps. When we only modify one source file, we only need to re-compile the modified one rather than compiling all the source files once again. This greatly reduces compiling time. 


#### 11. How can you use a global variable (全局变量) or function (函数) in several source files (源文件)? Please give as many ways as you can.

- For a global variable: define it in one `.cpp` file, and use "`extern`" keyword to declare it a header file. Wherever do we want to use the global variable, we can simply include the header file. For functions, it is similar. The only difference is that the "`extern`" keyword could be omitted.
- Pass them as arguments of functions.

#### 12. Is it possible to redefine a variable or function with the keyword "extern"? For example, "extern int a = 2;". Why?

- No. Because variable "`a`" has been defined in another place, and "`extern int a = 2;`" is equal to "`int a = 2;`". This will cause redefinition error.
- As mentioned above, if we want to use "`a`", then we should declare it with "`extern int a;`". And it is best practice to store "`extern int a`" in the header file. 


#### 13. Please explain the usage of header files (头文件). Can we define the function body (函数体) in the header file? Do we need to compile header files using g++? Why?

- 头文件是用来使多文件项目可以顺利完成正常编译的必要部分。因为多文件项目中的某些编译单元定义了某些函数或者变量，而另一些编译单元又需要使用（调用）这些函数或者变量，此时我们把这些函数和变量的声明统一放在一个头文件之中，这样我们只需要在每个编译单元之中使用预处理器将头文件包含进去，就可以正常完成编译，而不会出现未声明就使用的错误。而且，头文件使整个项目中出现的函数和变量列出，显得十分有条理。
- 在头文件中，对于普通函数的定义是不允许的，因为这样可能出现链接时出现重复定义的错误，普通函数可以多次声明但不可以多次定义。但是如果是内联函数，就必须写在头文件之中，不能写在任何其他的编译单元之中，否则在分段编译形成目标文件之后，对应的内联函数的标识符就会被编译器自动替换为整个函数体，此时该标识符就不存在了，于是在其他的编译单元中调用该内联函数时就会报错。
- 头文件是不需要单独编译的，因为头文件之中只是一些函数和变量等等的声明而已，通过预处理过程被包含进独立的编译单元之中，成为该编译单元的一部分，此时参与到编译之中。

#### 14. Please explain the differences between "" and  <>  when including a header file in the source file.

- `#include <headerfile>`:  
  The compiler will search from the standard library directory. This method is typically used to include header files in the standard library. We may modify the “include search path” (include的文件搜索路径) in the following ways:   
  (1) environmental variable “`PATH`” (通过环境变量设置);   
  (2) in the compiler option, e.g., `g++ -Idir/to/header` (通过编译选项设置).

- `#include "headerfile"`:  
  The compiler will first search from the user’s working directory. This method is typically used to include user-defined header files. If the header is not found in the current directory, then the compiler will search again in the same directories as "`<>`".


##	Make and makefile
#### 15. Please explain the dependency rules of make.

- The symbol in front of the colon is the target. If the target is a file, and its modification date is older than any dependencies after the colon or the target does not exist, the following commands will be executed.
  ```makefile
  target: file1 file2 file3
      command to generate target
  file1: file12 file13
      command to generate file1
  ```

#### 16. On Linux, how do we enable separate compilation (分段编译) of source files using make and makefile? Assume that we have the files main.cpp, sum.cpp, product.cpp, and functions.h; write a makefile to generate an executable named test by separate compilation.

```makefile
all: test
test: main.o sum.o product.o functions.h
	g++ main.o sum.o product.o -o main.exe
sum.o: sum.cpp
	g++ -c sum.cpp -o sum.o
product.o: product.cpp
	g++ -c product.cpp -o product.o
main.o: main.cpp
	g++ -c main.cpp -o main.o
clean:
	rm *.o
	rm test
```

#### 17. On linux, how can we generate a binary file with a makefile? How can we use a library file to generate an executable file with makefile? Please give a simple example on Linux.

```cpp
/*  mylib.h  */
#ifndef MYLIB_H
#define MYLIB_H

void fun();

#endif
```

```cpp
/*  main.cpp  */
#include <iostream>
#include "mylib.h"
using namespace std;

int main()
{
	fun();
	return 0;
}
```

```makefile
/* makefile */
all:main
main:main.o
	g++ main.o mylib.a -o main
main.o:main.cpp
	g++ -c main.cpp -o main.o
clean:
	rm main.o main
```

```makefile
/* a more complex makefile including how to generate and use libs */
lSOURCES=$(wildcard *.cxx)
sSOURCES=$(wildcard *.cpp)
HEADERS=$(wildcard *.h)
lOBJECTS=$(lSOURCES:%.cxx=%.o)
sOBJECTS=$(sSOURCES:%.cpp=%.o)
TARGET=maze.exe
LIB=maze.a

all: $(TARGET) $(LIB)
$(TARGET): $(sOBJECTS) $(HEADERS) $(LIB)
	@echo "Now Generating $(TARGET) ..."
	g++ $(sOBJECTS) $(LIB) -o $(TARGET)
$(LIB): $(lOBJECTS) $(HEADERS)
	@echo "Now Generating $(LIB) ..."
	ar -rv $(LIB) $(lOBJECTS)
	ranlib $(LIB)
%.o: %.cpp $(HEADERS)
	@echo "Now Compiling $< ..."
	g++ -c $< -o $@
%.o: %.cxx $(HEADERS)
	@echo "Now Compiling $< ..."
	g++ -c $< -o $@
clean:
	del *.o *.exe *.bak *.a
explain:
	@echo "Lib Sources: $(lSOURCES)"
	@echo "User Sources: $(sSOURCES)"
	@echo "Lib Objects: $(lOBJECTS)"
	@echo "User Objects: $(sOBJECTS)"
	@echo "Lib: $(LIB)"
	@echo "Target: $(TARGET)"
```

#### 18. Please explain more options for make, which are the command-line arguments of make.

```plain
 Options:
	-b, -m                                        Ignored for compatibility.
	-B, --always-make                             Unconditionally make all targets.
	-C DIRECTORY, --directory=DIRECTORY           Change to DIRECTORY before doing anything.
	-d                                            Print lots of debugging information.
	--debeg[=FLAGS]                               Print various types of debugging information.
	-e, --environment-overrides                   Environment variables override makefiles.
	-f FILE, --file=FILE, --makefile=FILE         Read FILE as a makefile
	-I, --ignore-errors		                      Ignore errors from commands.
	-I DIRECTORY, --include-dir=DIRECTORY         Search DIRECTORY for included makefiles
	-j [N], --jobs[=N]                            Allow N jobs at once; infinite jobs with no arg.
	-k, --keep-going                              Keep going when some targets can’t be made.
	-l [N], --load-average[=N], --max-load[=N]    Don’t start multiple jobs unless load is below N.
	-L, --check-symlink-times                     Use the latest mtime between symlinks and target.
	-n, --just-print, --dry-run, --recon          Don’t actually run any commands; just print them.
	-o FILE, --old-file=FILE, --assume-old=FILE   Condier FILE to be very old and don’t remake it.
	-p, --print-data-base                         Print make’s internal database.
	-q, --question                                Run no commands; exit status says if up to date.
	-r, --no-builtin-rules                        Disable the built-in implicit rules.
	-R, --no-builtin-variables                    Disable the built-in variable settings.
	-S, --no-keep-going, --stop                   Turns off –k.
	-t, --touch                                   Touch targets instead of remaking them.
```

**19.	Please list as many useful advanced grammars (高级语法) of makefile as many as you can. If possible, explain the usage of these grammars. For example, it is convenient to automatically detect all the source files in a folder (自动检测文件夹下的所有文件) and automatically compile them all. How does makefile support this?**

- Assume there are source files `a.cpp`, `b.cpp`, and `c.cpp` in the folder, along with the header file `func.h`, we can complie the program in the following way:
    ```makefile
	object=a.o b.o c.o
	main: func.h
		g++ $(object) –o main
	```
	Using "`$`", we may define variables for batch processing.

- Infact, we can make the above process more automaticlly using the following makefile (JACK OF ALL TRADES!):

```makefile
cc = g++
prom = ./main  # target
deps = $(shell find ./ -name "*.h")  # dependence
src = $(shell find ./ -name "*.cpp")  # source code
obj = $(src:%.cpp=%.o)  # object file
 
$(prom): $(obj)
	$(cc) $(obj) -o $(prom) -std=c++2a -Wall
 
%.o: %.cpp $(deps)
	$(cc) $< -o $@ -std=c++2a -c -Wall
```

Explanation: Using the shell command `find`, we can automaticlly detect all source files (`*.cpp` matches all the files with a `.cpp` extension, etc. the source file) and all header files (`*.h` matches all the files with a `.h` extension, etc. the header file). `prom` is the name of our wanted executable file, when we type `make` in the command line, the make program will automaticlly find all source files and header files to compile (create or update) our target (in this case, that is the `./main`)

- ".RECIPEPREFIX = >" can change all the tab into '>'.

- In Makefile, we can use Bash grammars as follows.
	```makefile
	ifeq ($(CC),gcc)
		libs=$(libs_for_gcc)
	else
		libs=$(normal_libs)
	endif
	```
