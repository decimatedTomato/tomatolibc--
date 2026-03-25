#include <type_traits>
#include <utility>

#ifdef DEBUG
#include <iostream>
#endif

namespace tomato
{
template<typename T>
class UniquePtr
{
  private:
    T *data;

  public:
    UniquePtr() noexcept
        : data(nullptr)
    {
    }
    UniquePtr(T *ptr) noexcept
        : data(ptr)
    {
    }
    ~UniquePtr()
    {
        if (data)
        {
            delete data;
        }
    }
    UniquePtr(UniquePtr &&rhs) noexcept
        : data(rhs.release())
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
        return data;
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
        T *old = std::exchange(data, ptr);
        if (old)
        {
            delete old;
        }
    }

    void swap(UniquePtr &rhs) noexcept
    {
        rhs.data = std::exchange(data, rhs.data);
    }

#ifdef DEBUG
    void println(const char *variable_name) const
    {
        using namespace std;
        cout << "Dereferencing " << variable_name << " gives " << data;
        if (data)
            cout << " -> " << *data;
        cout << endl;
    }
#endif
};

template<typename T, typename... Args>
UniquePtr<T> make_unique(Args &&...args)
{
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}
} // namespace tomato
