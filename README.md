此仓库记录我看《C++ Templates》第二版（目前只有英文版）的读书笔记

代码在code文件夹里

以下为笔记目录：

# 第一部分：基本概念

## 1.Function Templates /第一章  函数模板

* [1.1 A First Look at Function Template /初识函数模板](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch1/1.1%20A%20First%20Look%20at%20Function%20Templates.md)
  * [1.1.1 Defining the Template /定义模板](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch1/1.1.1%20Defining%20the%20Template.md)
  * [1.1.2 Using the Template /使用模板](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch1/1.1.2%20Using%20the%20Template.md)
  * [1.1.3 Two-phase Translation /二阶段翻译](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch1/1.1.3%20Two-Phase%20Translation.md)
* [1.2 Template Argument Deduction /模板实参](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch1/1.2%20Template%20Argument%20Deduction.md)
* [1.3 Multiple Template Parameters /多模板参数](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch1/1.3%20Multiple%20Template%20Parameters.md)
  * [1.3.1 Template Parameters for Return Types /属于返回类型的模板参数](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch1/1.3.1%20Template%20Parameters%20for%20Return%20Types.md)
  * [1.3.2 Deducing the Return Type /推断返回类型](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch1/1.3.2%20Deducing%20the%20Return%20Type.md)
  * [1.3.3 Return Type as CommonType /作为通用类型返回](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch1/1.3.3%20Return%20Type%20as%20Common%20Type.md)
* [1.4 Default Template Arguments /默认模板实参](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch1/1.4%20Default%20Template%20Arguments.md)
* [1.5 Overloading Function Template /重载函数模板](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch1/1.5%20Overloading%20Function%20Templates.md)

## 10.Basic Template Terminology /第10章  基本模板术语

* [10.1 "Class Template" or "Template Class"](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch10/10.1%20Class%20Template%20or%20Template%20Class%20.md)

* [10.2 Substitution,Instantiation,and Specialization](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch10/10.2%20Substitution%EF%BC%8CInstantiation%EF%BC%8Cand%20Specialization.md)
* [10.3 Declarations versus Definitions /声明对定义](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch10/10.3%20Declarations%20versus%20Definitions.md)

* [10.4 The One-Definition Rule /唯一定义原则](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch10/10.4%20The%20One-Definition%20Rule.md)

* [10.5 Template Arguments versus Template Parameters /模板实参对模板参数](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch10/10.5%20Template%20Arguments%20versus%20Template%20Parameters.md) 

# 第二部分 深入模板

## 14.Instantiation /第14章  实例化

* [14.1 On-Demand Instantiation /按需实例化](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch14/14.1%20On-Demand%20Instantiation.md)

* [14.2 Lazy Instantiation /延迟实例化](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch14/14.2%20Lazy%20Instantiation.md)
  * [14.2.1 Partial and Full Instantiation /部分实例化和全实例化](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch14/14.2.1%20Partial%20and%20Full%20Instantiation.md)
  * [14.2.2 Instantiated Components /实例化组件](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch14/14.2.2%20Instantiated%20Components.md)

* [14.3 The C++ Instantiation Model /C++实例化模型](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch14/14.3%20The%20C%2B%2B%20Instantiation%20Model.md)
  * [14.3.1 Two-Phase Lookup /二阶段查找](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch14/14.3.1%20Two-phase%20Lookup.md)
  * [14.3.2 Points of Instantiation /实例化点](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch14/14.3.2%20Points%20of%20Instantiation.md)
  * [14.3.3 The Inclusion Model](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch14/14.3.3%20The%20Inclusion%20Model.md)

* [14.5 Explicit Instantiation /显式实例化](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch14/14.5%20Explicit%20Instantiation.md)
  * [14.5.1 Manual Instantiation /手动实例化](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch14/14.5.1%20Manual%20Instantiation.md)
  * [14.5.2 Explicit Instantiation Declarations /显式实例化声明](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch14/14.5.2%20Explicit%20Instantiation%20Declaration.md)

* [14.6 Compile-Time if Statement /编译时if语句](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch14/14.6%20Compile-Time%20if%20Statements.md)

* [14.7 In the Standard Libaray /在标准库中](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch14/14.7%20In%20the%20Standard%20Libaray.md)

# 第三部分：模板和设计

## 19.Implementing Traits /第19章 实现Traits

* [19.3 Type Function /类型函数](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch19/19.3%20Type%20Function.md)
  * [19.3.1 Element Types /元素类型](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch19/19.3.1%20Element%20Type.md)
  * [19.3.2 Transformation Traits /转换特性](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch19/19.3.2%20Transformation%20Traits.md)
  * [19.3.3 Predicate Traits /谓词特性](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch19/19.3.3%20Perdicate%20Traits.md)
  * [19.3.4 Result Type Traits /返回类型特性](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch19/19.3.4%20Result%20Type%20Traits.md)

* 19.4 SFINAE-Based Traits /基于SFINAE的特性
  * [19.4.1 SFINAE Out Function Overloads /SFINAE Out 函数重载](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch19/19.4.1%20SFINAE%20Out%20Function%20Overloads.md)
  * [19.4.2 SFINAE Out Partial Specialization /SFINAE Out 偏特化](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch19/19.4.2%20SFINAE%20Out%20Partial%20Specialization.md)
  * [19.4.3 Using Generic Lambdas for SFINAE /为SFINAE使用泛型lambda](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch19/19.4.3%20Using%20Generic%20Lambda%20for%20SFINAE.md)
  * [19.4.4 SFINAE-Friendly Traits /SFINAE友好特性](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch19/19.4.4%20SFINAE-Friendly.md)

* [19.5 IsConvertibleT](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch19/19.5%20IsConvertibleT.md)

* 19.6 Detecting Members /检查成员
  * [19.6.1 Detecting Member Types /检查成员类型](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch19/19.6.1%20Detecting%20Member%20Types.md)
  * [19.6.2 Detecting Arbitrary Member Types /检查任意成员类型](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch19/19.6.2%20Detecting%20Arbitrary%20Member%20Types.md)
  * [19.6.3 Detecting NonType Members /检查非类型成员](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch19/19.6.3%20Detecting%20Nontype%20Member.md)

* 19.7 Other Techniques /其他Trait技术
  * [19.7.1 If-Then-Else](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch19/19.7.1%20IfThenElse.md)

## 21.Template and Inheritance /第21章  模板和继承

* [21.2 The Curiously Recurring Template Pattern(CRTP) /奇异循环模板模式](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch21/21.2%20CRTP.md)
  * [21.2.1 The Barton-Nackman Trick](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch21/21.2.1%20The%20Barton-Nackman%20Trick.md)
  * [21.2.2 Operator Implementations /运算符实现](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch21/21.2.2%20Operator%20Implements.md)
  * [21.2.3 Facades /外观模式](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch21/21.2.3%20Facades.md)

## [22.Bridging Static and Dynamic Polymorphism/桥接静态和动态多态](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch22/preface.md)

* [22.1 Function Objects,Pointers,and std::function<> /函数对象，指针和std::function<>](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch22/22.1%20Function%20Objects%2CPointers%2Cand%20stdfunction.md)
* [22.2 Generalized Function Pointers /广义函数指针](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch22/22.2%20Generalized%20Function%20Pointers.md)
* [22.3 Bridge Interface /桥接口](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch22/22.3%20Bridge%20Interface.md)
* [22.4 Type Erasure /类型擦除](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch22/22.4%20Type%20erasure.md)
* [22.5 Optional Bridging /可选桥接](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch22/22.5%20Optional%20Bridging.md)
* [22.6 Performance Consideration /性能考虑](https://github.com/Conzxy/CppTemplates_2nd/blob/main/ch22/22.6%20Performance%20Considerations.md)

## [23.Metaprogramming/元编程]()

* [Notes]()

* [23.1 The State of Modern C++ Metaprogramming]()
  * [23.1.1 Value Metaprogramming /值元编程]()
  * [23.1.2 Type Metaprogramming /类型元编程]()
  * [23.1.3 Hybrid Metaprogramming /混合元编程]()
  * [23.1.4 Hybrid Metaprogramming For Unit Types /单元类型的混合元编程]()

* [23.2 The Dimensions of Reflective Metaprogramming/反射元编程的维度]()
* [23.4 Computational Completences /计算完备性]()

