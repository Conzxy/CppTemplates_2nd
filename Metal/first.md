# Metal 学习体会

# 偏特化的分支写法

我在《CPPT2nd》上看到的带有谓词的偏特化分支多为`bool`作为第二模板参数，但是这有局限性：很多情况只支持一个分支

比如`has_enum_value<>`：

```cpp
template<class val,bool =
    	 std::is_enum_v<decltype(val::value)>>
struct has_enum_value
    :std::true_type{};

template<class val>
struct has_enum_value<val,false>
	:std::false_type{};
```

很好，那么下面呢：

```cpp
template<class val, class=std::true_type>
struct has_integral_value_impl
	:has_enum_value<val> {};

template<class val>
struct has_integral_value_impl<val, typename
		is_pointer_to_const_integral<decltype(&val::value)>::type>
	:std::true_type {};

template<class val>
struct has_integral_value_impl<val, typename
				std::is_member_pointer<decltype(val::value)>::type>
	:std::false_type {};
```

你如果要用bool设计，就得准备两个bool，因为有两个谓词，随着谓词的数目增多，bool的参数个数也会随之增多，这种设计是欠缺考虑的，你可能会说设置默认bool为true，然后后面谓词按该方式设置，很抱歉，偏特化规定：`非类型参数只能为非依赖性或plain`，因此，设置默认类型才是合适的方式√

这其实就是元编程的编译时测试，`std::true_type`和`std::false_type`可以视为tag（当然只是视作，和tag dispatching是有区别的，这个依赖的是偏特化）

# integral/enum谓词

```cpp
template<class val,class =std::true_type>
struct has_enum_value
    :std::false_type{};

template<class val>
struct has_enum_value<val,typename
    				  std::is_enum<decltype(val::value)>::type>
	:std::true_type{};

template<class val>
struct is_pointer_to_const_integral
    :std::false_type{};

template<class val>
struct is_pointer_to_const_integral<val const*>
    :std::is_integral<val>{};

template<class val,class =std::true_type>
struct has_integral_value_impl
    :has_enum_value<val>{};

template<class val>
struct has_integral_value_impl<val,typename
    					  	   is_pointer_to_const_integral<
    					  	   decltype(&val::value)>::type>
	:std::true_type{};

template<class val>
struct has_integral_value_impl<val,typename
    						   std::is_member_pointer<
    						   decltype(&val::value)>::type>
    :std::false_type{};

template<class val,class =std::true_type>
struct has_integral_value:has_integral_value_impl<val>{};

template<class val>
struct has_integral_value<val,typename 
    					  std::is_enum<val>::type>
	:has_enum_value<val>{};
```

我们规定`has`谓词都是针对测试类型的`value`成员，`is`谓词针对测试类型本身

## has_integral_value_impl

我们要知道`enum`的潜在类型只能是整型且无法取址（&），故主模板（fall back）继承`has_enum_value`

有两个偏特化分支：

* 判断是否为常量可以用`is_pointer_to_const_integral`，如果为`std::true_type`，则继承`std::true_type`，这个不难理解

* 判断是否为成员指针，这个为什么有必要呢？（以下成员指针指pointer to member)

  首先，我们要明确需要的value是不依赖于对象而依附于类型的，即`static`，如果value不是静态的，那么&就会得到成员指针，因为非静态成员依赖于对象，这和成员指针的使用匹配的，而静态成员取址则会得到一般指针，不会受限于类作用域：

  ```cpp
  struct test_ {
  	int const value;
  };
  struct test {
  	//enum e :int{};
  	static int const value=2;
  };
  
  std::is_member_pointer_v<decltype(&test::value)>;	//false
  std::is_member_pointer_v<decltype(&test_::value)>;	//true
  //or...
  typeid(decltype(&test::value)).name();		//int const*
  typeid(decltype(&test_::value)).name();		//int const test_::*
  ```

  所以判断是否为成员指针是为了将非静态value踢出去，而让静态value退回其他特化分支

* 这里还有个问题值得考虑：两个分支会不会引起二义性？

  并不会。因为`is_pointer_to_const_integral`只针对非成员指针，因此这个特化分支设计是合理的

  ```cpp
  metal::detail::is_pointer_to_const_integral<decltype(&test::value)>::value;		//true
  metal::detail::is_pointer_to_const_integral<decltype(&test_::value)>::value;	//false
  ```

  想要表示成员指针必须写成`C::*`（其中C为模板参数）

## has_integral_value

`has_integral_value`有一个特化：

* 主模板继承`has_integral_value_impl<>`

* 特化则判断是否枚举，如果为，则继承`has_enum_value<>`

  这个应该是我们不需要枚举，如果的确是，则判断其保存的value成员是否为枚举，为枚举的情况则使用该枚举进行计算，其实这和我们元编程（特别是值元编程）的习惯有关，不太可能会用枚举作为容器储存我们需要的value成员（你能保证不用枚举存枚举，那这个特化基本不会被选择）

