#include <string>
#include <iostream>

class IteratorFacadeAccess {
    template<typename Derived, typename Value, typename Category,
            typename Reference, typename Distance>
    friend class IteratorFacade;

    // 所有迭代器的要求
    template<typename Reference, typename Iterator>
    static Reference dereference(Iterator const& i)
    {
        return i.dereference();
    }

    template<typename Pointer,typename Iterator>
    static Pointer arrow(const Iterator& i){
        return i.arrow();
    }

    template<typename Iterator>
    static void increment(Iterator& i){
        i.increment();
    }
    template<typename Iterator>
    static bool equals(Iterator& i,Iterator& other){
        return i.equals(other);
    }

    // 双向迭代器的要求
    template<typename Iterator>
    static void decrement(Iterator& i)
    {
        i.decrement();
    }


    // 随机访问迭代器的要求
    template<typename Iterator, typename Distance>
    static void advance(Iterator& i, Distance n)
    {
        i.advance(n);
    }

    template<typename Distance,typename Iterator>
    static Distance measureDistance(Iterator& x,Iterator& y){
        return x.measureDistance(y);
    }

    template<typename Iterator>
    static bool lessthan(Iterator& x,Iterator& y){
        return x.lessthan(y);
    }

    template<typename Iterator,typename Distance>
    static Iterator plus(Iterator& i,Distance n){
        return i.plus(n);
    }
};

template<typename Derived,typename Value,typename Category,
         typename Reference=Value&,typename Distance=std::ptrdiff_t>
class IteratorFacade{
public:
    using value_type=typename std::remove_const_t<Value>;
    using reference=Reference;
    using pointer=Value*;
    using difference_type=Distance;
    using iterator_category=Category;

    //input iterator interface:
    reference operator*()const{
        return IteratorFacadeAccess::dereference<reference>(asDerived());
    }

    pointer operator->()const{
        return IteratorFacadeAccess::arrow<pointer>(asDerived());
    }

    Derived& operator++(){
        IteratorFacadeAccess::increment(asDerived());
        return asDerived();
    }

    Derived operator++(int){
        Derived result=asDerived();
        IteratorFacadeAccess::increment(asDerived());
        return asDerived();
    }

    friend bool operator==(IteratorFacade const& lhs,
                           IteratorFacade const& rhs){
        return equals_helper(lhs,rhs);
    }

    friend bool operator!=(IteratorFacade const& lhs,
                           IteratorFacade const& rhs){
        return !(lhs==rhs);
    }
    //bidirectional iterator interface:
    Derived& operator--(){
        IteratorFacadeAccess::decrement(asDerived());
        return asDerived();
    }

    Derived operator--(int){
        Derived result{asDerived()};
        IteratorFacadeAccess::decrement(asDerived());
        return result;
    }

    //random access iterator interface:
    reference operator[](difference_type n)const{
        return IteratorFacadeAccess::dereference<reference>(
                IteratorFacadeAccess::plus(asDerived(),n)
                );
    }

    Derived operator+(difference_type n)const{
        return IteratorFacadeAccess::plus(asDerived(),n);
    }

    Derived& operator+=(difference_type n){
        IteratorFacadeAccess::advance(asDerived(),n);
        return asDerived();
    }

    Derived& operator-=(difference_type n){
        IteratorFacadeAccess::advance(asDerived(),-n);
        return asDerived();
    }

    friend difference_type operator-(IteratorFacade const& lhs,
                                     IteratorFacade const& rhs){
        return measureDistance_helper(lhs,rhs);
    }

    friend bool operator<(IteratorFacade const& lhs,
                          IteratorFacade const& rhs){
        return lessthan_helper(lhs,rhs);
    }

    friend bool operator>=(IteratorFacade const& lhs,
                           IteratorFacade const& rhs){
        return !(lhs<rhs);
    }

    friend bool operator>(IteratorFacade const& lhs,
                          IteratorFacade const& rhs){
        return rhs<lhs;
    }

    friend bool operator<=(IteratorFacade const& lhs,
                           IteratorFacade const& rhs){
        return !(lhs>rhs);
    }

    friend Derived operator+(difference_type n,IteratorFacade& i){
        return i+n;
    }
private:
    Derived& asDerived(){
        return *static_cast<Derived*>(this);
    }

    Derived const& asDerived()const{
        return *static_cast<Derived const*>(this);
    }

    static bool equals_helper(IteratorFacade const& lhs,
                              IteratorFacade const& rhs){
        return IteratorFacadeAccess::equals(lhs.asDerived(),rhs.asDerived());
    }

    static difference_type measureDistance_helper(IteratorFacade const& lhs,
                                              IteratorFacade const& rhs){
        return IteratorFacadeAccess::measureDistance<difference_type>(lhs.asDerived(),rhs.asDerived());
    }

    static bool lessthan_helper(IteratorFacade const& lhs,
                         IteratorFacade const& rhs){
        return IteratorFacadeAccess::lessthan(lhs.asDerived(),rhs.asDerived());
    }
};



template<typename Iterator,typename T>
class ProjectionIterator:public IteratorFacade<
        ProjectionIterator<Iterator,T>,
        T,
        typename std::iterator_traits<Iterator>::iterator_category,
        T&,
        typename std::iterator_traits<Iterator>::difference_type>{
    using Base=typename std::iterator_traits<Iterator>::value_type;
    using Distance=typename std::iterator_traits<Iterator>::difference_type;

    Iterator iter;
    T Base::* member;

    friend class IteratorFacadeAccess;
    //implement:
    T& dereference()const{
        return (*iter).*member;
    }

    void increment(){
        ++iter;
    }

    bool equals(ProjectionIterator const& other)const{
        return iter==other.iter;
    }

    void decrement(){
        --iter;
    }

    //require:random access iterator
    Distance measureDistance(ProjectionIterator const& other)const{
        return iter - other.iter;
    }

    bool lessthan(ProjectionIterator const& other)const{
        return iter<other.iter;
    }

    void advance(Distance n){
        iter+=n;
    }

    ProjectionIterator plus(Distance n)const{
        return {iter+n,member};
    }
public:
    ProjectionIterator(Iterator it ,T Base::* pm)
    :iter(it),member(pm){}
};

template<typename Iterator,typename Base,typename T>
auto project(Iterator iter,T Base::* pm){
    return ProjectionIterator<Iterator,T>(iter,pm);
}

struct Person{
    std::string firstname;
    std::string lastname;

    friend std::ostream& operator<<(std::ostream& os,Person const& person){
        return os<<person.firstname<<"·"<<person.lastname;
    }
};
