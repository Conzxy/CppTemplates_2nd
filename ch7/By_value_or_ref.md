# 传值还是传引用？

## 传参方式

* X				 (value)
* X const&   (const ref)
* X &             (lvalue)
* X &&           (rvalue)

* T &&           (universal)

无特殊理由一般推荐传值，自从C++17的copy optimization和C++11的move semantic的引入，除左值外我们都可以将拷贝的开销略去(如果该左值不再使用也可以move)

但是如果

* 拷贝被禁止(disable copy copy-ctor/copy=)
* 参数用来返回(reference)
* 转发参数(universal reference)

* 性能优化(avoid copy)

我们往往会考虑用引用

## non-const lvalue-reference

```cpp
template<typename T>
void f(T& arg){
    //do something
}
```

但是如果`T`推断为`XX const`，而函数体内修改了`arg`,违背了我用non-const左值引用的意图，并触发error

解决方法：

* `static_cast`触发compile-time error

```cpp
template<typename T>
void f(T& arg){
	static_cast(!std::is_const<T>::value,"");
}
```

* 用`std::enable_if<>`禁用该情形

```cpp
template<typename T,
		typename =std::enable_if_t<!std::is_const_v<T>>>
void f(T& arg){
    //do something
}
```

## std::ref and std::cref

定义在`<functional>`中，用于传值时你也想传引用，