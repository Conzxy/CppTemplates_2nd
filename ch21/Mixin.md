# 反射元编程的维度

值元编程基于constexpr求值（[§23.1.1]()），而类型元编程基于递归模板实例化（[§23.1.2]()）

但是你要知道constexpr在上古时代可是没有这东西的，但是照样玩的溜（e.g. Loki库），值元编程也可以由递归模板实例化产生，我们来看一下该视点下的平方根求值：

```cpp
template<int N,int lo=1,int hi=N>
struct Sqrt{
	static constexpr auto mid=(lo+hi+1)/2;
    static constexpr auto value=(N<mid*mid)?Sqrt<N,lo,mid-1>
        								   :Sqrt<N,mid,hi>;
};

template<int N,int M>
struct Sqrt<N,M,M>{
    static constexpr auto value=M;
};
```

由于依赖的是非类型实参而不是函数实参，这个对浮点数就很不友好。。。