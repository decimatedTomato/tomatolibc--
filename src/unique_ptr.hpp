#include <type_traits>
#include <utility>

namespace tomato {

template<typename T>
class UniquePtr
{
private:
    T *data;

public:
    static UniquePtr make_unique(T data)
    {
        UniquePtr ret(data);
        return ret;
    }
    ~UniquePtr()
    {
        delete data;
    }
    UniquePtr(UniquePtr&& rhs) noexcept
    : data(std::exchange(rhs.data, nullptr))
    {
    }
    UniquePtr& operator=(UniquePtr&& rhs) noexcept
    {
        if (this != &rhs)
        {
            delete data;
            data = rhs.data;
            rhs.data = nullptr;
        }
        return *this;
    }

    T *get() const noexcept
    {
        return *data;
    }
    std::add_lvalue_reference<T>::type operator*() const noexcept
    {
        return *data;
    }
    T *operator->() const noexcept
    {
        return get(); 
    }
    
    private:
    UniquePtr(T data)
    : data(new T(data))
    {}
};
} // namespace tomato
