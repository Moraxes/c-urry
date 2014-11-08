#include <memory>
#include <functional>


template <typename RetT, typename ArgT1, typename... ArgTs>
class Curried
{
    std::function<RetT(ArgT1, ArgTs...)> fptr;

public:
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
