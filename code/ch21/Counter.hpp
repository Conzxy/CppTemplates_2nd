template<typename CountType>
class Counter{
protected:
    constexpr Counter(){ ++created;++alive; }
    constexpr Counter(Counter const&){ ++created;++alive; }
    constexpr Counter(Counter &&){ ++created;++alive; }
    ~Counter(){ --alive; }
private:
    inline static std::size_t created=0;
    inline static std::size_t alive=0;
public:
    static constexpr std::size_t num_of_created(){
        return created;
    }
    static constexpr std::size_t num_of_alive(){
        return alive;
    }
};
