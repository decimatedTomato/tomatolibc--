#include <type_traits>
#include <utility>

namespace tomato
{

template <typename T> class UniquePtr
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
        if (data)
        {
            delete data;
        }
    }
    UniquePtr(UniquePtr &&rhs) noexcept : data(rhs.release())
    {
    }
    UniquePtr &operator=(UniquePtr &&rhs) noexcept
    {
        if (this != &rhs)
        {
            reset(rhs.release());
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

    T *release() noexcept
    {
        return std::exchange(data, nullptr);
    }

    void reset(T *ptr = nullptr) noexcept
    {
        T * old = std::exchange(data, ptr);
        if (old)
        {
            delete old;
        }
    }

  private:
    UniquePtr(T data) : data(new T(data))
    {
    }
};
} // namespace tomato
