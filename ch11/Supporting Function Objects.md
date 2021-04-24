# Supporting Function Objects
callable有一个很好的用途就是作为泛型算法的回调函数（call back），比如<alogorithm>中的泛型算法
这里举一个for_each的例子：
```cpp
template<typename II,typename Func>
Func foreach(II first,II last,Func func)
{
    for(first != last)
    {
        func(*first);
        ++first;
    }
}
```
这个函数可以适配于之前我们所提到的任何callable除了pointer-to-member