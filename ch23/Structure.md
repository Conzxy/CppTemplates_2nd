# 元编程的不同

一般的程序是直接编写程序，编译生成目标代码，然后在**运行期执行**

而模板元编程（*TMP*）则是借助语言提供的**模板机制**，通过编译器推断，在编译时得到程序，该程序通过进一步的编译，如此最终得到目标代码（即在编译时*程序编写程序*并执行）

# 元编程的基本演算

C++的模板机制是**图灵完备**的，因此可以实现完整的元编程，你可以声明变量、执行循环、编写及调用函数...，与一般编程无异，但全部都是发生在编译时

元编程的演算规则有两种：

* **编译时测试**——**选择**
* **编译时迭代**——**迭代**

当然，元编程还可以通过模板参数传递不同的**策略**（policy），实现**依赖注入**（dependency injection）/**控制反转**（inversion of control），比如`std::vector<typename T,typename Allocator=std::allocator<T>>`可以自定义内存分配器

## 编译时测试

实现`if-else/switch`的选择逻辑

C++17前，通过特化和重载实现——找到合适的模板匹配

C++17后，可以通过[`constexpr if`](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch14/14.6%20Compile-Time%20if%20Statements.md)这个语法糖来改变以前冗余的编写方式

逃不掉的是这些条件依赖于traits模板

## 编译时迭代

实现`for/while/do`的循环逻辑

C++17前，递归和特化或重载结合，特化或重载用于终止递归（递归模板实例化）

C++17后，有了`折叠表达式`这个语法糖，简化了迭代写法

实际上在`constexpr函数`中用`while/for`语句也能在编译时循环

# 应用（作用）

利用元编程，可以很方便的设计出**类型安全**、**运行时高效**的程序，但是过度使用，则会**增加编译时间**，另一方面会**降低程序的可读性**（其实自C++11标准后每次新标准都会多一些支持元编程的语法）

三类基本应用：

* **数值计算**
  * 编译时常数计算
  * 优化表达式计算
* **类型推断**
* **代码生成**

最开始的元编程就是数值计算，可以编译时进行常量的计算，并利用**表达式模板**（*expression template*），实现部分求值、惰性求值、简化表达式等

类型推断和泛型编程不太一样，泛型编程只是提供一套**通用概念**，而元编程进行*任意类型之间的相互推断*

代码生成则是依赖于模板机制实现控制结构，控制编译器生成新代码：往往通过**编译时测试**和**编译时迭代**的演算规则推断出来

# 编译性能

Chiel Douwes对比了几种**模板操作的代价**（*Costs of operations：The Rule of Chiel*）（并没有提到C++14的变量模板）（从高到低呈金字塔状）：

* SFINAE
* 实例化 函数模板
* 实例化 类模板
* 调用 别名模板
* 添加参数到 一个类型（比如添加给 类模板）
* 添加参数到 别名模板的调用中
* 查找已缓存的类型（Looking up a memorized type）

最后这个例子如下：

```cpp
template <typename x>
struct f {
  using type = x;
};

f<int>::type; // instantiate f<int>
f<int>::type; // f<int> is already instantiated, nothing is done.
```

基于以上原则，**直接**基于别名模板的`std::conditional_t<>`和**直接**基于变量模板的`std::is_same_v<>`都比传统基于`std::is_same<>`和`std::conditional<>`的要高效：

```cpp
//传统方法
template<typename T1,typename T2>
struct is_same:std::false_type{};

template<typename T>
struct is_same<T,T>:std::true_type{};

template<typename T1,typename T2>
constexpr bool is_same_v=is_same<T1,T2>::value;

//直接基于变量模板
template<typename T1,typename T2>
constexpr bool is_same_v=false;

template<typename T>
constexpr bool is_same_v<T,T>=true;

--------------------------------------------------------------------------------------
//传统方法
template<bool ,typename T,typename F>
struct conditional{
    using type=T;
};

template<typename T,typename F>
struct conditional<false,T,F>{
    using type=F;
};

template<bool B,typename T,typename F>
using conditional_t=typename conditional<B,T,F>::type;

//直接基于别名模板
template<bool>
struct conditional{
    template<typename T,typename F>
    using type=T;
};

template<>
struct conditional<false,T,F>{
    template<typename T,typename F>
    using type=F;
};

template<bool B,typename T,typename F>
using conditional_t=typename conditional<B>::template type<T,F>;
//将类模板的T和F添加到alias，根据chiel规则，是可能比传统方法更快的（实际数据表示的确更快）
```

# 一般函数递归和递归模板实例化的差别

一般函数递归，首先需要压栈，再来并没有生成新的代码，而递归模板实例化会生成不同的实例，生成了新的代码，同时可以减少栈的深度（一般来说，隐式实例化只有需要才会进行，实例化点也就不一样，但是定义不可能生成多份，因此我觉得碰到相同的实例应该会压栈）

*TMP*的支柱就是**递归模板实例化**（Recurring template instantiation）