# type_traits_base.h

```cpp
template<typename T,T val>
struct Integral_constant{
    static constexpr T value=val;
    using value_type=T;
    using type=Integral_constant;
    
    constexpr operator value_type()const noexcept{
        return val;
    }
    
    constexpr value_type operator ()()const noexcept{
        return val;
    }
}

template<bool B>
using Bool_constant=Integral_constant<bool,B>;

using _true_type=Bool_constant<true>;
using _false_type=Bool_constant<false>;
```

