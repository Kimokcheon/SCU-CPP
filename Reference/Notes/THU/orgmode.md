
# Table of Contents

1.  [org-mode 的基本情况](#orgadebede)
    1.  [org-mode 的历史](#org02b0f10)
    2.  [why not markdown?](#orge786aa1)
    3.  [如何进入 org-mode](#org193c1f4)
2.  [org-mode 能做什么](#orga8c8893)
    1.  [文本标记](#org77d2d70)
    2.  [层次管理](#org79e440d)
    3.  [链接](#org6cd6f7a)
    4.  [表格体系](#org38111ad)
    5.  [代码块的插入](#org875ff70)
    6.  [时间管理](#org9345df8)
3.  [org-mode 的应用](#orgdf66916)
    1.  [多种多样的导出方式](#org4c28bcb)
    2.  [编写 repo 的文档](#org7ef261b)



<a id="orgadebede"></a>

# org-mode 的基本情况


<a id="org02b0f10"></a>

## org-mode 的历史

org-mode, 是 Carsten Dominik 在 2003 年推出的一款文本标记语言, 其最早的作用是管理日常生活 <del>ddl</del>, 并进行简单的富文本编辑. 之所以在 emacs 之后讲, 是因为 emacs 在很早的版本就提供了对 org-mode 的支持, 当然还有一套完整的 emacs 风格的快捷键体系.


<a id="orge786aa1"></a>

## why not markdown?

首先, markdown 是于 2004 年推出的第一个发行版, 历史上不如 org-mode 早; 其次, markdown 的扩展性极为有限, 而 emacs 的超强扩展性, 使得 org-mode 具有极其多样化的功能. 此外, org-mode 还可以进行计划的规划 <del>,让你化身时间管理大师</del>.


<a id="org193c1f4"></a>

## 如何进入 org-mode

只需要创建一个 `*.org` 的文件并使用 emacs 打开, 即可自动进入 org-mode; 另外, 你还可以通过 `M-x <RET> org-mode <RET>` 来对任意的 buffer 运行 org-mode.


<a id="orga8c8893"></a>

# org-mode 能做什么


<a id="org77d2d70"></a>

## 文本标记

和 markdown 一样, 其具备了 markdown 所有的功能, 但是其扩展性更胜一筹, 下面是一些常见的命令:

1.  Commands     :B_block:

    `=abc=`: `abc` ; `+abc+`: <del>abc</del>
    
    `/abc/`: *abc* ; `*abc*`: **abc** (在通常情况下是加粗, 而 slides 中该效果不明显, 因此改为了彩色)
    
    `\(E=mc^2\)`: \(E=mc^2\)
    
    当然还有行间公式 `\[\]`:
    
    \[\begin{aligned} \nabla\cdot\vec{E} &=& \frac{\rho}{\epsilon_0} \\ \nabla\cdot\vec{B} &=& 0 \\ \nabla\times\vec{E} &=& -\frac{\partial B}{\partial t} \\ \nabla\times\vec{B} &=& \mu_0\left(\vec{J}+\epsilon_0\frac{\partial E}{\partial t} \right) \end{aligned}\]


<a id="org79e440d"></a>

## 层次管理


用过 markdown 的同学们知道, markdown 中管理标题的等级是使用 `#` 来管理的, 而且最多只有 5 个. 对于一些极端的情况是不够用的.
    
在 org-mode 中, 使用的是 `*`, 但是不限个数. 而且受限于编辑器, 层次管理是一个很大的问题. 而在 emacs 中, 存在大量的快捷键对不同的标题层次, 以一棵有根树的形式, 进行管理. 而且可以对不同的层次进行折叠, 例如不显示低于某一级别的标题, 便于观察文章结构.


例如, 使用 `M-S-<left>/<right>` 可以对整个子树中的所有标题升降一级, 而 `C-c C-p/C-n` 可以跳转到上一个/下一个标题, `C-c C-f/C-n` 可以跳转到相同等级的上一个/下一个标题.


<a id="org6cd6f7a"></a>

## 链接

org-mode 中, 可以加入不同类型的链接. 链接可以指向网页 url, 本地文件, 邮箱, org 文档中的一个元素, 等等. 通常的语法是 `[[link][description]]`


<a id="org38111ad"></a>

## 表格体系

你可以像纯文本那样, 直接用 `|` 和回车创建一个表格, 又可以像在 M$ Excel 中那样, 使用 `$` 符号取出单元格中的值, 并进行简单的数学运算.

1.  Example     :B_block:

        | Number | Price | Total   |
        |--------+-------+---------|
        |      2 |  3.45 | =$1*$2  |
        |      4 |  4.34 |         |
        |      5 |  3.44 |         |
        |      5 |   5.6 |         |
    
    对于这样的一个表格, 只要输入 `C-u C-c C-c`, 就会自动完成计算.


<a id="org875ff70"></a>

## 代码块的插入

使用 `#+begin_src #+end_src` 即可插入一段代码块, 并且会自动加载你使用的对应语言的配置文件, 包括高亮, 缩进等, 当然比较简单的快捷键是 `C-c C-, s`, 而在这样的环境中, 使用 `C-c '` , 就会直接开启一个新的 `buffer`, 你可以在这种语言的代码编辑环境中直接编写代码块.   

1.  Example     :B_block:

        #include<iostream>
        
        int main(){
            std::cout<<"Hello, Org Mode"<<std::endl;
            return 0;
        }
    
    另外, 还有 latex, quote, example 等环境, 使得 org-mode 可以支持很复杂的编辑命令.


<a id="org9345df8"></a>

## 时间管理


org-mode 中, 可以用 `C-c,C-t` 来快速的插入一个时间, 默认的状态是 `TODO`, 按 `<tab>` 可以切换到 `DONE` 的阶段. 由于 emacs 极强的扩展性, 你可以自定义任何想要的时间状态, 例如 `WAITING,RUNNING` 等等.


此外, emacs 还有多样化的快捷键, 帮助你管理这些事件. 例如集体改变状态, 找出所有的 `TODO`, 跳到下一个 `DONE` 等等, 都有内置的或者自定义的快捷键来实现.


而且 emacs 可以自动监视编辑文本的总时间, 从而统计你做一项任务的实际时间. 配合 \`\`番茄钟'' 方法, 能极大的提高时间管理的效率.


<a id="orgdf66916"></a>

# org-mode 的应用


<a id="org4c28bcb"></a>

## 多种多样的导出方式

写好的 org-mode 文件, 可以转化为 LaTeX,HTML,ODT 等不同的文件类型, 而其中最重要的就是 LaTeX, 在 org-mode, 你可以直接内嵌一段 LaTeX 代码, 例如引入 `tikz` 宏包来画图等等. 当然, 还可以内嵌 HTML, 让你的代码可以接受网站的 css 或 js 的渲染. 这个 slide, 就是通过 LaTeX 中的 beamer 模式导出的.


<a id="org7ef261b"></a>

## 编写 repo 的文档

这个 **[repo](https://github.com/snosov1/toc-org/)** 是一个为 org-mode 提供类似 md 中 `[TOC]` 功能的 elisp 代码.

![img](/home/jiang/Pictures/shot.png)

如果仔细看, 我们发现文档是 `README.org` 而非 `README.md`! 这说明, github 是支持以 `.org` 为扩展名的文档, 并且会对其做出正确的渲染.


<div class="org-center">
<p>
谢谢大家!
</p>
</div>

