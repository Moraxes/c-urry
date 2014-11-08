#include <memory>  // std::shared_ptr
#include <functional>  // std::function


template <typename RetT, typename ArgT1, typename... ArgTs>
class Curried
{
public:
    std::function<RetT(ArgT1, ArgTs...)> fptr;

    Curried(decltype(fptr) fptr) :
        fptr(fptr)
    {}

    auto operator () (ArgT1 x)
    { 
        std::shared_ptr<decltype(fptr)> fsptr(new decltype(fptr)(fptr));

        return Curried<RetT, ArgTs...>(
            [fsptr, x] (ArgTs... args) {
                return (*fsptr)(x, args...);
        });
    }
};

template <typename RetT, typename ArgT1>
class Curried <RetT, ArgT1>
{
    std::function<RetT(ArgT1)> fptr;

public:
    Curried(decltype(fptr) fptr) :
        fptr(fptr)
    {}

    RetT operator () (ArgT1 x)
    {
        return fptr(x);
    }
};

template <typename RetT, typename... ArgTs>
auto curry(RetT (*f)(ArgTs...))
{
    return Curried<RetT, ArgTs...>(f);
}

template <typename RetT, typename... ArgTs>
auto curry(std::function<RetT(ArgTs...)> f)
{
    return Curried<RetT, ArgTs...>(f);
}

template <typename RetT, typename... ArgTs>
auto uncurry(Curried<RetT, ArgTs...> cf)
{
    return cf.fptr;
}
