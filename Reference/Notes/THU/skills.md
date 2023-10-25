# This page lists the useful programming skills for better efficiency, preferrably with an illustrating example (最好有代码实例展示).


## Use this function to input integers for better efficency.
```C++
void G (int &n) {
    bool f;
    char a;
    for (f = 0, a = getchar(); !isdigit(a); a = getchar()) if (a == '-') f = 1;
    for (; isdigit(a); a = getchar()) n = n * 10 + a - '0';
    if (f) n = -n;
}
```

## vector对象的清空

对vector对象vec调用``clear``方法时，是不能释放其存储的内存的。如果要释放其内存，可以使用下面的方法：

```c++
vec.swap(vector<int>());
```

## SFINAE

SFINAE /s’fi:nei/ is short for “Substitution Failure Is Not An Error”. It is a black magic widely used in C++ template metaprogramming. This feature applies during overload resolution.

In C++, different functions can have the same name. When you call a function, the compiler will maintain a set of functions that have the called name. Overload resolution is the process that selects the fittest function from the set. The compiler will first discard functions which can’t match the given arguments. Here is an example:

```c++
#include <iostream>
#include <type_traits>

struct Foo {};
struct Bar {};

static_assert(!std::is_convertible_v<Foo, Bar> &&
              !std::is_convertible_v<Bar, Foo>);

void func(Foo) { std::cout << "func(Foo) is called." << std::endl; }
void func(Bar) { std::cout << "func(Bar) is called." << std::endl; }

int main() {
  Foo foo;
  func(foo);
}

// output: func(Foo) is called.
```

Though the function `void func(Bar)` can’t match the given argument `foo`, it doesn’t cause a compile error.

If a function in the set is actually a function template, it gets complicated. The compiler has to substitute the template parameters. If the substitution fails, SFINAE rule will be applied and the compiler will simply remove this function template from the set without declaring an error. Here is an example:

```c++
#include <iostream>

struct Foo {};

template <typename Type>
void func(Type, decltype(Type::m_x)) {
  std::cout << "func(Type,decltype(Type::m_x)) is called." << std::endl;
}

void func(Foo, int) { std::cout << "func(Foo,int) is called." << std::endl; }

int main() {
  Foo foo;
  func(foo, 0);
}

// output: func(Foo,int) is called.
```

`Foo` doesn’t have a member variable `m_x`, so after substituting `Type` with `Foo` in the function template `func`, `decltype(Type::m_x)` is invalid. Thus, this substitution fails, but there won’t be a compile error.

We can use SFINAE to add constraints to function templates and make the complier select the right one. In header file `type_traits`, there is a tool called `std::enable_if` and its convenient alias template helper `std::enable_if_t`. It has two template parameters. The first one is a non-type parameter `bool` and the second one is a type parameter(the default is `void`). If the non-type parameter is `true`, `std::enable_if_t` is just the same as the second type parameter, but if it is `false`, `std::enable_if` won’t have the member type `type` and `std::enable_if_t` will cause a substitution failure. Here is an example:

```c++
#include <iostream>
#include <type_traits>

template <typename Type>
auto func(Type) -> std::enable_if_t<std::is_integral_v<Type>> {
  std::cout << "This is the function for integers." << std::endl;
}

template <typename Type>
auto func(Type) -> std::enable_if_t<std::is_floating_point_v<Type>> {
  std::cout << "This is the function for floating numbers." << std::endl;
}

int main() {
  func(1);
  func(1.0);
}

// output:
//   This is the function for integers.
//   This is the function for floating numbers.
```

SFINAE has many applications. Here are some good uses: [C++ SFINAE examples](https://stackoverflow.com/questions/982808/c-sfinae-examples "Stack Overflow").
You can find more information [here](https://en.cppreference.com/w/cpp/language/sfinae "cppreference.com").

------
### A way to save the memory in dynamic programming (DP) problems

This skill can help you **save the memory** just using a one-dimension array instead of a two-dimension array when you are solving problems where *dynamic programming* is used. Check the two points listed as follows and then you can use the skill.

> [1] In your problem, you can get a new state of your solution space just by ***sequentially*** updating the last state in a way.
> [2] You don't care about the intermediate states. You only need the ***result*** .

#### Examples

[1] The 0-1 Knapsack Problem

There're n items w1,w2,...,wn whose values are v1,v2,...,vn and a knapsack whose capacity is C. Find a way to put some items in the knapsack and make it most valuable.

```cpp
/*Use a 2-dimension array
  dp[i][j]= the most value you can get when you are only allowed to use 0~ith items and a knapsack whose capacity is j, j<=C.
  w[i]= the storage the ith item will take up. 
  v[i]= the value of the ith item.*/
  
//The main part of the algorithm
//Initialize
for(int i=0;i<=n;++i)
	dp[i][0]=0;
for(int j=0;j<=C;++j)
	dp[0][j]=0;
//Update
for(int i=1;i<=n;++i)
	for(int j=1;j<=C;++j){
		if(w[i]<=j)
		//To pack or not
			dp[i][j]=max(dp[i-1][j-w[i]]+v[i],dp[i-1][j]);
		else
			dp[i][j]=dp[i-1][j];
	}
```
------
```cpp
/*Use a 1-dimension array
	dp[j]= the most value you can get when you are only allowed to use a knapsack whose capacity is j.
	w[i]= the storage the ith item will take up. 
	v[i]= the value of the ith item.*/

//The main part of the algorithm
//Initialize
for(int j=0;j<=C;++j)
	dp[j]=0;
/*Update
  When using a 2-dimension array, because you only need the information of the last row i-1 and the columns before j, you can actually update the 1-dimension array backwards so that the necessary information is not erased.*/
for(int i=1;i<=n;++i)
	for(int j=C;j>=w[i];--j){
		//To pack or not 
		dp[j]=max(dp[j-w[i]]+v[i],dp[j]);
	}
```

[2] The kth row in Yang Hui's Triangle

> The first 4 lines of Yang Hui's Triangle:
>                                                  1
>                                               1    1
>                                             1   2   1
>                                          1   3   3   1
```cpp
/*We use num[i][j] to present the number in ith row, jth column.(started from 0)
  As is known to all, num[i][j]=num[i-1][j-1]+num[i-1][j] for j=1,2,...,i-1 and num[i][0]=num[i][i]=1.
  We need the kth row of the Triangle*/

//Use a 2-dimension array
//The main part of the algorithm
for(int i=0;i<=k;++i)
	for(int j=0;j<=i;++j){
		if(j==0||j==i)
			num[i][j]=1;
		else{
			num[i][j]=num[i-1][j-1]+num[i-1][j];
		}
	}
```
------
```cpp
//Use a 1-dimension array
//The main part of the algorithm
/*When using a 2-dimension array, because you only need the information of the last row i-1 and the columns before j, you can actually update the 1-dimension array backwards so that the necessary information is not erased.*/
std::vector<int> num;
for(int i=0;i<=k;++i){
	num.push_back(1);//To match the number of elements in the ith row
	for(int j=i-1;j>=1;--j){
		num[j]+=num[j-1];
	}
}
```

## Logging with variadic function

A variadic function can accept variant numbers of parameters, it enables you to log any number of data as you wish.

You can define a variadic logging function like this:

```c++
#include <stdarg.h>
void PrintLog(const char* Format, ...) {
 	va_list args;  //NULL pointer now
  va_start(args, Format); //use va_start to point at the first variable
  //va_arg(args, char); you can use this function to point at next parameter with specific type
  vprintf(Format, args); // = printf(Format, ...)
  // you can add some other information, e.g. time, environment
  va_end(args);
}
```

This function can be used as `printf`.


## Detect Current Platform

You can rely on preprocessor to detect the current platform.

```c++
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
   //define something for Windows (32-bit and 64-bit, this part is common)
   #ifdef _WIN64
      //define something for Windows (64-bit only)
   #else
      //define something for Windows (32-bit only)
   #endif
#elif __APPLE__
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR
         // iOS Simulator
    #elif TARGET_OS_IPHONE
        // iOS device
    #elif TARGET_OS_MAC
        // Other kinds of Mac OS
    #else
    #   error "Unknown Apple platform"
    #endif
#elif __linux__
    // linux
#elif __unix__ // all unices not caught above
    // Unix
#elif defined(_POSIX_VERSION)
    // POSIX
#else
#   error "Unknown compiler"
#endif
```



## Filesystem Library (C++17)

The Filesystem library provides facilities for performing operations on file systems and their components. It's based on Boost::filesystem and finally merged into ISO C++. 

#### Path

First we need to get familiar with `path` class. This class is very easy to understand. Here is an example. (This example is under Mac OS, output under Windows maybe a little different)

```c++
#include <iostream>
#include <filesystem>
using namespace std;

int main() {
  filesystem::path mypath("/Users/FallDream/OOP_QA/skills.md");
  cout << "exists() = " << filesystem::exists(mypath) << "\n"
       << "root_name() = " << mypath.root_name() << "\n"
       << "root_path() = " << mypath.root_path() << "\n"
       << "relative_path() = " << mypath.relative_path() << "\n"
       << "parent_path() = " << mypath.parent_path() << "\n"
       << "parent_path().parent_path() = " << mypath.parent_path().parent_path() << "\n"
       << "filename() = " << mypath.filename() << "\n"
       << "stem() = " << mypath.stem() << "\n"
       << "extension() = " << mypath.extension() << "\n";
  for (auto& part : mypath) {
    cout << part << "\n";
  }
  return 0;
}
```

The output is like:

```
exists() = 1
root_name() = ""
root_path() = "/"
relative_path() = "Users/FallDream/OOP_QA/skills.md"
parent_path() = "/Users/FallDream/OOP_QA"
parent_path().parent_path() = "/Users/FallDream"
filename() = "skills.md"
stem() = "skills"
extension() = ".md"
"/"
"Users"
"FallDream"
"OOP_QA"
"skills.md"
```

You can use `/=` to concatenate two paths with a directory separator`/` and '+=' to only add a string.

```c++
mypath = "/Users/FallDream/"
mypath += "OOP_QA";  // "/Users/FallDream/OOP_QA"
mypath /= "skills.md";  // "/Users/FallDream/OOP_QA/skills.md"
```

#### Judge the type of a Path

Use `filesystem::status` to get the status of a path, and then judge its type.

```c++
void demo_status(const filesystem::path& p)
{
    std::cout << p;
    filesystem::file_status s = filesystem::status(p);
    if(filesystem::is_regular_file(s)) std::cout << " is a regular file\n";
    if(filesystem::is_directory(s)) std::cout << " is a directory\n";
    if(filesystem::is_block_file(s)) std::cout << " is a block device\n";
    if(filesystem::is_character_file(s)) std::cout << " is a character device\n";
    if(filesystem::is_fifo(s)) std::cout << " is a named IPC pipe\n";
    if(filesystem::is_socket(s)) std::cout << " is a named IPC socket\n";
    if(filesystem::is_symlink(s)) std::cout << " is a symlink\n";
    if(!filesystem::exists(s)) std::cout << " does not exist\n";
}
```

####  Go through all files under a directory

Use `filesystem::directory_iterator`.

```c++
filesystem::path mypath("/Users/FallDream/OOP_QA");
filesystem::directory_iterator list(mypath);
for (auto& i: list) {
  cout << i.path().filename() << "\n";
}
```

#### Other file operations

This library provides many useful functions that can be used to manage your files and directories. You can create, copy, rename or remove a file, get the lastest modification time, or create links.

For more information, see [cppreference](https://en.cppreference.com/w/cpp/filesystem).

## Log files

When programming, especially doing large projects, log files will be helpful for debugging. Do some output at certain points to files which are called "log files" using "fstream". This allows you to keep track of the running program and get to know where it stops without changing the original output of the program. Make sure when you have fixed all the bugs, it's easy to delete or comment the output code.

## Friend classes

Friend classes are not used often, but using them between classes which are closely connected can make coding easier and also save runtime. Friend classes can directly access the members of other classes, so when you need to change some private members(for example, sorting arrays), you can do it directly instead of using the interfaces. This saves runtime when you need to do this a lot of times in the program.

## 平方根倒数速算法

*Author* : Biru Yang     *Date*: 2020.6.27

**平方根倒数**指一个数的算术平方根的倒数（32位浮点数），这一计算在图形学中有大量的需求。

平方根倒数速算法最早可能于90年代由SGI发明，但直到2002-03年才在公共论坛上出现。

该算法首先接收一个32位带符号浮点数，然后将其作为32位整数看待，右移后以**魔法数字0x5f3759df**减之，如此使用牛顿迭代法反复跌倒，直至求出符合精确度要求的近似值。

代码如下：

```c++
float fast_reverse( float num )
{
    long i;
    float x, y;
    const float threehalfs = 1.5F;
    
    x = num * 0.5F;
    y = num;
    i = *(long *) &y;
    i = 0x5f3759df - (i >> 1);
    y = * (float *) &i;
    y = y * (threehalfs - (x * y * y));  //first iteration
    //y = y * (threehalfs - (x * y * y));  if necessary, second iteration
    
    return y;
}
```

若将其与以下使用math.h中sqrt()函数的版本相比：

```c++
float func_reverse( float num )
{
    return (1.0/sqrt(num));
}
```

+ **结果正确性** ：对于输入 **3.14159F** ，两者的返回值完全相同，均为 **0.564190** 。

+ **效率** ：

  + 百度百科词条是这样描述该算法的效率的：

    > 在计算浮点数的平方根倒数的同一精度的近似值时，此算法比直接使用浮点数除法要快四倍。
    
  + 但在我本地的编译器条件下，两个算法的时间基本相同（甚至第二个算法略快），运行10^8次后速算法用时0.518s，普通算法用时0.445s。可能是我的测试数据过于单一，在更为多样化的数据条件下也许其优势便会凸显。
---

该算法的更详细介绍（包括**魔法数字**的推导）见下文：[平方根倒数速算法](https://www.cnblogs.com/german-iris/p/5767546.html)

## Minimize the use of if/else branches

If there are are many *else* branches, and the test-condition is very close to the last *else* branch, the CPU may spending lots of time jumping from one *else* to another *else*. If possible, convert to a *switch* statement, then CPU only need to execute one jump with a lookup table.

## Minimize the use of function calls
Function calls require two jumps, and cause the compiler to manipulate stack memory. Consider using inline functions, and using iterations over recursion.

## Use ++i instead of i++ unless you have an explicit reason.
++i have a better efficiency than i++.

```cpp
for(int i = 0; i < 10; ++i)
```

instead of

```cpp
for(int i =  0; i < 10; i++)
```

Because `++i`  needn't call the copy constructor to build a new object `temp`.

`++i` is also faster than `i++` in `iterator` of STL.

because i++ creates a copy of the object, which, when not needed, is suboptimal.

## Use bit operations
When the operation involves powers of two, the bit operation can be used to solve the problem.  
For example, you can use a int as a bool[32].

## inline、const、&
+ Whenever you use a variable that never change, you'd better declare it as a const.
+ And for those function less than 10 lines, declare them as inline can improve the efficiency. 
+ For those large objects, it is costly to copy. So it better to use reference.

## Subset Enumeration

在二进制压位枚举子集时，一种非常便捷的写法：

```c++
for (int mask = 0; mask < tot; ++mask) {
    for (int submask = mask; submask; submask = (submask - 1) & mask) {
        ...
    }
}
```
一层循环即可枚举 submask 的所有子集（空集除外），进而 mask ^ submask 可以得到 mask 的所有真子集。

## Duff's device
在计算机科学领域，达夫设备（英文：Duff's device）是串行复制（serial copy）的一种优化实现，通过汇编语言编程时一常用方法，实现展开循环，进而提高执行效率。
原理上，在编程时，循环展开注重于利用批量处理，减少总处理分支数。而在串行复制数据时，当总循环次数无法被展开后循环的增量整除时，一般就用直接跳转到展开后循环体中部的方式，完成剩余数据的复制流程。
因此，根据循环展开的思想，针对串行复制数据的需要，以每次迭代时赋最多8个值的方式，用C语言写出了一个优化实现，成功优化了串行复制的效率。
例如：
send(to, from, count)
register short *to, *from;
register count;
{
	register n = (count + 7) / 8;
	switch (count % 8) {
	case 0:	do { *to = *from++;
	case 7:		 *to = *from++;
	case 6:		 *to = *from++;
	case 5:		 *to = *from++;
	case 4:	     *to = *from++;
	case 3:      *to = *from++;
	case 2:      *to = *from++;
	case 1:      *to = *from++;
	        } while (--n > 0);
	}
}
从速度上说，由于采用了循环展开技巧，使所需处理的分支数减少，从而降低了在处理分支时，中断与刷新流水线的巨大运算开销，因而相较于简单、直接的循环代码，这段代码的执行效率较高。
另外，由代码易知，若不带switch语句，则这段代码只能复制8*n个数据项，而若count无法为8整除，则仍有count%8（即count除于8的余数）项未处理；有鉴于此，此间嵌入了switch/case语句，负责处理剩余数据。
reference：https://zh.wikipedia.org/wiki/%E8%BE%BE%E5%A4%AB%E8%AE%BE%E5%A4%87

## Avoid the use of division
use b = *a\*0.2* instead of *b = a / 5* because computers are less efficient at division.

## 快速乘

当在C++中进行这种计算时可能因为不正确的结果：long long * long long % long long.

即int64与int64相乘的结果对int64取模，如果直接进行的话，有可能会因为溢出而得到错误的结果。在这种情况下，有一种比较简单但是速度比较慢的方法：（假设模数小于LLONG_MAX/2，否则在unsigned long long下运算即可)

```C++
long long mul(long long a,long long b,long long P)
{
    long long ret=0;
    for(;b;b>>=1,a=(a+a)%P)
        if(b&1)
            ret=(ret+b)%P;
    return ret;       
}
```

这个方法利用了快速幂的思想，单次的时间复杂度为$O(\log_2 b)$。

但实际上，有更加快速的方法，其代码为：

```C++
long long fast_mul(long long x,long long y,long long p)
{
	long long z=(long double)x/p*y;
	long long res=(unsigned long long)x*y-(unsigned long long)z*p;
	return (res+p)%p;
}
```

这份代码中，利用了$xy \bmod P=xy-\lceil \frac{xy}{P}\rceil *P$这个公式。

虽然在第四行有可能出现溢出的情况，但由于是unsigned long long的自然溢出，因此可以保证它们的差值是正确的。

这种方法的复杂度为$O(1)$。

## 快速幂
如果我们要计算$x^y$那么我们可以考虑利用倍增的思想，即通过每次平方算出$x^2,x^4,x^8,......,x^{2k}$并用这些结果相乘得到$x^y$需要乘法运算的次数变为原来的对数。代码如下：

```c++
int quickPow(int x,int y)
{
    int ans=1;
    while(y)
    {
        if(y&1)ans*=x;
        y>>=1;
        x*=x;
    }
    return ans;
}
```
## __builtin functions：

这些函数是C标准库中的一些函数，被GCC引入为内置函数。可以快速完成基础的位运算或其他功能，从而大幅优化关键位置效率。

`__builtin_popcount(uint32_t x)`：返回`x`二进制表示中`1`的个数。
`__builtin_ctz(uint32_t x)`：返回`x`二进制中最低位0的个数。注意`x=0`时返回值是未定义的。
`__builtin_clz(x)`：返回`x`二进制中最高位前导0的个数。注意`x=0`时返回值是未定义的。
`__builtin_bswap16(uint16_t x)`：返回16位整数字节顺序翻转的结果
`__builtin_bswap32(uint32_t x)`：返回32位整数字节顺序翻转的结果
`__builtin_bswap64(uint64_t x)`：返回64位整数字节顺序翻转的结果
`__builtin_except(bool x,true/false)`：表示期望这个`bool`表达式的真假，优化编译器的分支预测。
`__builtin_parity(uint32_t x)`：返回`x`的二进制中`1`个数的奇偶性。

**注意**：上述字节顺序翻转是指：以字节为单位将整数看作字符串，然后将这个字符串翻转。而非逐位取反。如`0xabcd -> 0xcdab`，`0x12345678 -> 0x78563412`）

更多请参考：https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html#Other-Builtins

## Multiple conditions in if
When we have a statement like `if (A && B)` and A is false, program will not check B.

Also statement like `if (A || B)` and A is true, program will not check B.

Sometime we may use it to realize some functions.

## unsigned int & int

​	在C/C++语言中，整数存在无符号整数(unsigned int)和有符号整数(int)两种数据类型，虽然表面上这种安排是很合理的：用unsigned int来表示不会小于0的整数(如长度、集合中的元素的枚举关系等等)，用int来表示有可能为负数的整数。但实践证明，这种安排带来的麻烦远远超过了他所带来的收益(让unsigned int 能表示的最大值相较于int提高了一倍)，以至于在之后的高级编程语言中都选择了废弃无符号整数这一数据类型。

​	为了理解这一点，我们首先要了解unsigned int 和 int类型的数据是如何在计算机中存储的。

​	unsigned int的存储是十分简单，由于所有数字都是非负数，所以他们直接以其二进制的表示方式存入计算机中，示例如下：

```c++
	unsigned int a = 10;		//0x0000000a
	unsigned int b = 100;		//0x00000064
	unsigned int c = 100000;	//0x000186a0
```

​	int的存储方式稍显复杂；首先int的最高位被用来做符号位，不能直接用于表示数字的大小；对于非负数的情况，存储方式与unsigned int相同，直接以二进制的表示方式存储；但对于负数，其是以补码的形式存储(对负数的绝对值的二进制取反再加1) 。采用这种方式的主要原因是为了让int之间的四则运算保持一致性，具体证明按下不表，同学们可自行寻找数电/计组教材学习。示例如下：

```c++
	int a = 10;			//0x0000000a
	int b = 100;		//0x00000064
	int c = 100000;		//0x000186a0
	int d = -1			//0xffffffff = ~0x00000001 + 1
	int e = -2000		//0xfffff830 = ~0x000007d0 + 1
```

​	这种存储方式带来的问题是：如果我们将值为负数的int强制转为unsigned int，我们就会得到一个很大的正数；如果我们将值为很大(超过int最大值)的unsigned int强制转为int，我们就会得到一个很小的负数。这往往会在程序内引发许多难以察觉但又会造成严重后果的问题。即便是经验丰富的程序员，也不一定能完全避免这类问题。

它可能导致程序运行错误：

```c++
/* WARNING: This is buggy code */
float sum_elements(float a[], unsigned int length)
{
    int i;
    float result = 0;
    
    for(i = 0; i <= length - 1; i++)
        result += a[i];
    return result;
}
```

这段代码试图计算数组a中所有元素的和，其中元素数量由length给出。但当我们传入length = 0时，代码并没有返回0的结果，而是出现了内存错误，原因就是length是unsigned int类型的，传入0后，length -1的十六进制表示为0xffffffff，但由于它是unsigned int类型，所以被翻译为了一个很大的正数，导致内存访问越界。

它可能导致运行结果错误：

```C++
/* Prototype for library function strlen */
size_t strlen(const char *s);

/* WARNING: This is buggy code */
bool str_longer(char *s, char *t)
{
    return strlen(s) - strlen(t) > 0;
}
```

这段代码试图返回s和t比较长度的结果，但由于strlen的返回类型为size_t(unsigned)，所以strlen(s) - strlen(t)即便为负数，但还是被翻译为了一个正数，进而返回了错误的结果。

它还甚至会让程序出现安全漏洞：

```c++
/* Declaration of library function memcpy */
void *memcpy(void *dest, void *src, size_t n);

/* Kernel memory region holding user-accessible data */
#define KSIZE 1024
char kbuf[KSIZE]
    
/* Copy at most maxlen bytes from kernel region to user buffer */
int copy_from_kernel(void *user_dest, int maxlen)
{
    int len = KSIZE < maxlen ? KSIZE : maxlen;
    memcpy(user_dest, kbuf, len);
    return len;
}
```

​	copy_from_kernel函数的主要功能是将系统内核中的数据复制到用户的缓冲区中，但如果用户是怀有恶意的攻击者，他就会传入maxlen为一个负数值，此时长度len就会以负数的形式传入memcpy中，但由于memcpy的接受类型为size_t(unsigned)，那么实际上在复制的过程中，n就会被翻译为的一个很大的正数，进而会把内核内的许多额外信息复制到用户的缓冲区，尽管不一定能够完全复制出来，但攻击者还是会看到很多其未被授权查看的信息。

由此可见，unsigned int 会带来很多让人意想不到的麻烦，因此，最好的解决方案就是：

#### 尽量避免使用unsigned int这个数据类型！


## 使用nullptr

nullptr是c++11用来表示空指针新引入的常量值，在c++中表示空指针语义时，建议使用nullptr而不要使用NULL，因为NULL本质上是个int型的0，其实不是个指针。

```c++
void func(void *ptr) {
    cout << "func ptr" << endl;
}

void func(int i) {
    cout << "func i" << endl;
}

int main() {
    func(NULL); // 编译失败，会产生二义性
    func(nullptr); // 输出func ptr
    return 0;
}
```

## Loop unrolling
Normal Loop

```c++
 int x;
 for (x = 0; x < 100; x++)
 {
     delete(x);
 }
```
After loop unrolling

```c++
 int x; 
 for (x = 0; x < 100; x += 5 )
 {
     delete(x);
     delete(x + 1);
     delete(x + 2);
     delete(x + 3);
     delete(x + 4);
 }
```
The goal of loop unwinding/unrolling is to increase a program's speed by reducing or eliminating instructions that control the loop. Optimizing compilers will sometimes perform the unrolling automatically, or upon request. But the code may become less readable after loop unrolling.

## Allow small error in accuracy rather than using == operator when comparing two floating-point numbers
As we all know, it is inevitable that error will occur when doing floating-point calculations. So instead of using `if(a==b)`, use `if(fabs(a-b)<EPS)`, where EPS is a very small number, for example 1E-7.

## 数组的多重循环按行遍历
例如下面的程序：
```c++
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;
int main()
{
	const int MAX_ROW = 2000;
	const int MAX_COL = 2000;
	int(*a)[MAX_COL] = new int[MAX_ROW][MAX_COL];
	clock_t start, finish;

	//先行后列
	start = clock();
	for (int i = 0; i<MAX_ROW; i++)
	for (int j = 0; j<MAX_COL; j++)
		a[i][j] = 1;
	finish = clock();
	//totaltime=(double)()/CLOCKS_PER_SEC;
	cout << "先行后列遍历时间为：" << finish - start << "ms" << endl;
	//先列后行
	start = clock();
	for (int i = 0; i<MAX_COL; i++)
	for (int j = 0; j<MAX_ROW; j++)
		a[j][i] = 1;
	finish = clock();
	//totaltime=(double)()/CLOCKS_PER_SEC;
	cout << "先列后行遍历时间为：" << finish - start << "ms" << endl;

	return 0;
}
```
这个程序的结果为：11ms，20ms
由于行遍历的连续性，按行遍历可以快速找到下一个内存的指针，从而效率更高。
