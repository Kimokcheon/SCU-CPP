在头文件中包含`Calculator.h`

```c++
#include "Calculator.h"
```

创建一个计算器实例

```c++
Calculator calc;
```

通过`input()`函数传入求值表达式与赋值表达式字符串，然后调用`calculate()`进行求值，对于求值表达式默认返回并打印结果，对于赋值表达式仅返回等号右边计算结果，错误表达式会抛出异常。

单个`Calculator`实例具有记忆功能，会记住历史输入的所有自定义变量，如果要清除自定义变量内存，可以调用`Calculator::clear`。

一个简单的例子如下：

```c++
#include <iostream>
#include <string>

#include "Calculator.h"

using namespace std;

int main() {
    string exp;
    Calculator calc;
    while (getline(cin, exp)) {
         calc.input(exp);
         try {
             calc.calculate();
         } catch (exception &e) {
             cerr << e.what() << endl;
         }
    }
    return 0;
}
```

------

2023/03/27
