# 基于类型属性的重载

## tag dispatching

这个最为经典的就是基于iterator_catogory的算法重载了。

这个不多说，没有涉及SFINAE

## Enable/Disable Templates

由模板`std::enable_if`结合SFINAE可以禁用模板

该模板实现十分简单：

```cpp
template<bool, typename T = void>
struct Enable_if{    
};

template<typename T>
struct Enable_if<true, T>{
    using type = T;
}

template<bool Cond, typename T = void>
using Enable_if_t = typename Enable_if<Cond, T>::type;
```

使用`std::enable_if`需要注意重声明问题

```cpp
template<typename Iterator,
		 typename = std::enable_if_t<condition>>
void f();

template<typename Iterator,
		 typename = std::enable_if_t<condition2>>
void f();			//ERROR: redeclaration
```

尽管条件不同，但是模板实参列表是等价的：**<tyename, typename>**，默认实参是不考虑的。

有两种方式回避该问题：

* dummy parameter

  ```cpp
  template<typename Iterator,
  		 typename = std::enable_if_t<condition>>
  void f();
  
  template<typename Iterator,
  		 typename = std::enable_if_t<condition2>,
  		 typename = int>	//dummy parameter:int
  void f();
  ```

* default non-type parameter

  ```cpp
  template<typename Iterator,
  		 std::enable_if_t<condition, int> = 0>
  void f();
  
  template<typename Iterator,
  		 std::enable_if_t<condition2, double> = 0>
  void f();
  ```

* as return type

  ```cpp
  template<typename Iterator>
  std::enable_if_t<condition> f();
  
  template<typename Iterator>
  std::enable_if_t<condition2> f();
  ```

简而来说，就是signature不能一致

## Instantiation-Safe Template

所谓实例化安全模板是指：实例化绝对不会失败的模板

这种模板可以通过`std::enable_if_t `结合SFINAE traits实现，因为如果不满足条件，那么SFINAE将substitution fail转换成deduction fail从而抛弃该模板，因此并不会进入实例化阶段，而满足条件的才会进行实例化，这种模板即是*Instantiation-Safe Template*

### Example

```cpp
template<typename T>
T const& min(T const& x, T const& y){
    if(y < x){		//requires operator < 
        return y;
    }
    return x;
}
```

因此提供HasLess谓词（基于SFINAE）

```cpp
template<typename T>
struct Identity;

template<typename T1, typename T2>
struct HasLess{
private:
	template<typename U1, typename U2>
    static std::true_type
    test(Identity<decltype(std::declval<U1>() < std::declval<U2>()));
    
    template<typename U1, typename U2>
	static std::false_type
    test(...);
public:
    using type = decltype(test<T1, T2>(nullptr));
    static constexpr bool value = decltype(test<T1, T2>(nullptr))::value;
};

template<typename T1, typename T2, typename HasLess>
struct LessResultT{
    using type = decltype(std::declval<T1>() < std::declval<T2>());
};

template<typename T1, typename T2>
struct LessResultT<T1, T2, std::false_type>
{};

template<typename T1, typename T2>
struct LessResult : LessResultT<T1, T2, typename HasLess<T1, T2>::type>
{};

template<typename T1, typename T2>
using LessResult_t = typename LessResult::type;
```

min改良版：

```cpp
template<
typename T, 
std::enable_if_t<
 std::convertible<LessResult_t<T const&, T const&>, 
				  bool>::value, 
			     int>> = 0
>
T const& min(T const& x, T const& y){
	if(y < x)
        return y
    return x;
}
```

