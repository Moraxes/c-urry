#include <memory>  // std::shared_ptr
#include <functional>  // std::function


template <typename RetT, typename ArgT1, typename... ArgTs>
class Curried
{
public:
    std::function<RetT(ArgT1, ArgTs...)> func_obj;

    Curried(decltype(func_obj) func_obj) :
        func_obj(func_obj)
    {}

    auto operator () (ArgT1 x)
    { 
        std::shared_ptr<decltype(func_obj)> fsptr(new decltype(func_obj)(func_obj));

        return Curried<RetT, ArgTs...>(
            [fsptr, x] (ArgTs... args) {
                return (*fsptr)(x, args...);
        });
    }
};

template <typename RetT, typename ArgT1>
class Curried <RetT, ArgT1>
{
    std::function<RetT(ArgT1)> func_obj;

public:
    Curried(decltype(func_obj) func_obj) :
        func_obj(func_obj)
    {}

    RetT operator () (ArgT1 x)
    {
        return func_obj(x);
    }
};

template <typename RetT, typename... ArgTs>
auto curry(RetT (*func)(ArgTs...))
{
    return Curried<RetT, ArgTs...>(func);
}

template <typename RetT, typename... ArgTs>
auto curry(std::function<RetT(ArgTs...)> func)
{
    return Curried<RetT, ArgTs...>(func);
}

template <typename RetT, typename... ArgTs>
auto uncurry(Curried<RetT, ArgTs...> cfunc)
{
    return cfunc.func_obj;
}
