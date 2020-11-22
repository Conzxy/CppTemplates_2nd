#ifndef TEST_TYPE_ERASURE_H
#define TEST_TYPE_ERASURE_H

#include <utility>
#include <type_traits>
#include <stdexcept>

template<typename T>
class IsEqualComparable{
private:
    static void* conv(bool);
    template<typename U>
    static std::true_type test(decltype(conv(std::declval<U const&>()==std::declval<U const&>())),
                        decltype(conv(!(std:: declval<U const&>()==std::declval<U const&>()))));
    template<typename >
    static std::false_type test(...);
public:
    static constexpr bool value=decltype(test<T>(nullptr,nullptr))::value;
};

template<typename T,bool =IsEqualComparable<T>::value>
class TryEquals{
public:
    static bool equals(T const& x,T const& y){
        return x==y;
    }
};

struct NotEqualityComparable:public std::exception{};

template<typename T>
class TryEquals<T,false>{
public:
    static bool equals(T const& x,T const& y){
        throw NotEqualityComparable();
    }
};

template<typename R,typename... Args>
class FunctorBridge{
public:
    virtual ~FunctorBridge(){}
    virtual FunctorBridge* clone()const=0;
    virtual R invoke(Args... args)const=0;
    virtual bool equals(FunctorBridge const* fb)const=0;
};

template<typename Functor,typename R,typename... Args>
class SpecificFunctorBridge:public FunctorBridge<R,Args...>{
    Functor functor;
public:
    template<typename FunctorFwd>
    SpecificFunctorBridge(FunctorFwd&& functor)
     : functor(std::forward<FunctorFwd>(functor)){
    }

    virtual SpecificFunctorBridge* clone()const override{
        return new SpecificFunctorBridge(functor);
    }

    virtual R invoke(Args... args)const override{
        return functor(std::forward<Args>(args)...);
    }

    virtual bool equals(FunctorBridge<R,Args...> const* fb)const override{
        if(auto specFb=dynamic_cast<SpecificFunctorBridge const*>(fb))
            return TryEquals<Functor>::equals(functor,specFb->functor);
        else
            return false;
    }
};

template<typename Signature>
class Function;

template<typename R,typename... Args>
class Function<R(Args...)>{
private:
    FunctorBridge<R,Args...>* bridge;
public:
    Function():bridge(nullptr){}
    Function(Function const& other):bridge(nullptr){
        if(other.bridge){
            bridge=other.bridge->clone();
        }
    }

    Function(Function &other)
      : Function(static_cast<Function const&>(other)){
    }

    Function(Function &&other):bridge(other.bridge){
	    other.bridge=nullptr;
    }

    template<typename F>
    Function(F&& f):bridge(nullptr){
        using Functor=std::decay_t<F>;
        using Bridge=SpecificFunctorBridge<Functor,R,Args...>;
        bridge=new Bridge(std::forward<F>(f));
    }

    Function& operator=(Function const& other){
	    Function tmp(other);
	    swap(*this,tmp);
	    return *this;
    }

    Function& operator=(Function &&other){
	    delete bridge;
	    bridge=other.bridge;
	    other.bridge=nullptr;
	    return *this;
    }

    template<typename F>
    Function& operator=(F&& f){
	    Function tmp(std::forward<F>(f));
	    swap(*this,tmp);
	    return *this;
    }

    ~Function(){
	    delete bridge;
    }

    friend void swap(Function& f1,Function& f2){
	    std::swap(f1.bridge,f2.bridge);
    }

    explicit operator bool()const{
	    return bridge!=nullptr;
    }

    //invocation
    R operator()(Args... args)const{
        return bridge->invoke(std::forward<Args>(args)...);
    }

    friend bool operator==(Function const& f1,Function const& f2){
        if(!f1||!f2){
            return !f1&&!f2;
        }
        else
            return f1.bridge->equals(f2.bridge);
    }

    friend bool operator!=(Function const& f1,Function const& f2){
        return !(f1==f2);
    }
};


#endif //TEST_TYPE_ERASURE_H
