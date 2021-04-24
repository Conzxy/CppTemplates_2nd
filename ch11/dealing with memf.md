# dealing with member function and additional arguments
之前提到不能应对成员指针，同时也无法与额外实参搭配调用，我们可以用std::C++17的invoke解决这个问题：
```cpp
template<typename II,typename Func,typename ...Args>
Func for_each(II first,II last,Func func,Args... args)
{
    while(first != last)
    {
        TinySTL::invoke(func,TinySTL::forward<Args>(args)...,*first);
        ++first;
    }
    return func;
}
```
于是，我们可以愉快地这么写：
```cpp
struct FunObj
{
    void f(int x) const { print("member function called for {}\n",x); }
};


int main()
{
    TinySTL::vector<int> primes{2,3,5,7,11,13,17,19};
    TinySTL::for_each(primes.begin(),primes.end(),
                    &FunObj::f,FunObj{});

    TinySTL::for_each(primes.begin(),primes.end(),
                [](char const* prefix,int i){
                    print("{:s} {:d}\n",prefix,i);
                },"- value:");
}
```
不仅可以处理pointer-to-member-function，还可以给callback函数添加额外参数（比如这里的prefix）


## 补充：TinySTL::invoke实现
C++17:
```cpp
namespace detail{
        template<typename >
        inline constexpr bool Is_reference_wrapper_v=false;
        template<typename T>
        inline constexpr bool Is_reference_wrapper_v<reference_wrapper<T>> =true;

        template<typename B,typename D,typename FM,typename ...Args>
        constexpr decltype(auto)
        invoke_impl(FM B::*f,D&& obj,Args&&... args)
        {
            if constexpr(Is_member_function_pointer_v<decltype(f)>)
            {
                if constexpr(Is_base_of_v<B,TinySTL::Decay_t<D>>)
                    return (TinySTL::forward<D>(obj).*f)(TinySTL::forward<Args>(args)...);
                else if constexpr(Is_reference_wrapper_v<Decay_t<D>>)
                    return (obj.get().*f)(TinySTL::forward<Args>(args)...);
                else
                    return (*TinySTL::forward<D>(obj).*f)(TinySTL::forward<Args>(args)...);
            }
            else
            {
                static_assert(Is_member_object_pointer_v<decltype(f)>);
                static_assert(sizeof...(Args)==0); 
                if constexpr(Is_base_of_v<B,Decay_t<D>>)
                    return TinySTL::forward<D>(obj).*f;  
                else if constexpr(Is_reference_wrapper_v<Decay_t<D>>)
                    return obj.get().*f;
                else
                    return *TinySTL::forward<D>(obj).*f;
            }
        }
    

        template<typename F,typename ...Args>
        constexpr decltype(auto)
        invoke_impl(F&& f,Args&&... args)
        {
            return TinySTL::forward<F>(f)(TinySTL::forward<Args>(args)...);
        }
    }

    template<typename F,typename ...Args>
    constexpr decltype(auto)
    invoke(F&& f,Args&&... args) noexcept(noexcept(f))
    {
        return detail::invoke_impl(std::forward<F>(f),std::forward<Args>(args)...);
    }
}
```
C++11:
```cpp
namespace detail {
template <class F, class... Args>
inline auto INVOKE(F&& f, Args&&... args) ->
    decltype(std::forward<F>(f)(std::forward<Args>(args)...)) {
      return std::forward<F>(f)(std::forward<Args>(args)...);
}

template <class Base, class T, class Derived>
inline auto INVOKE(T Base::*pmd, Derived&& ref) ->
    decltype(std::forward<Derived>(ref).*pmd) {
      return std::forward<Derived>(ref).*pmd;
}

template <class PMD, class Pointer>
inline auto INVOKE(PMD pmd, Pointer&& ptr) ->
    decltype((*std::forward<Pointer>(ptr)).*pmd) {
      return (*std::forward<Pointer>(ptr)).*pmd;
}

//SFINAE can also applies to
//return type
template <class Base, class T, class Derived, class... Args>
inline auto INVOKE(T Base::*pmf, Derived&& ref, Args&&... args) ->
    decltype((std::forward<Derived>(ref).*pmf)(std::forward<Args>(args)...)) {
      return (std::forward<Derived>(ref).*pmf)(std::forward<Args>(args)...);
}

template <class PMF, class Pointer, class... Args>
inline auto INVOKE(PMF pmf, Pointer&& ptr, Args&&... args) ->
    decltype(((*std::forward<Pointer>(ptr)).*pmf)(std::forward<Args>(args)...)) {
      return ((*std::forward<Pointer>(ptr)).*pmf)(std::forward<Args>(args)...);
}
} // namespace detail

template< class F, class... ArgTypes>
auto invoke(F&& f, ArgTypes&&... args) ->
    decltype(detail::INVOKE(std::forward<F>(f),std::forward<ArgTypes>(args)...)){
    return detail::INVOKE(std::forward<F>(f), std::forward<ArgTypes>(args)...);
}
```