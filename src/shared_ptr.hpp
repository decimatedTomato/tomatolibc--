#include <atomic>
#include <type_traits>
#include <utility>

#ifdef DEBUG
#include <iostream>
#endif

namespace tomato
{
template <typename T>
class SharedPtr
{
  private:
    T                *data;
    std::atomic<int> *rc;

  public:
    SharedPtr() noexcept : data(nullptr), rc(nullptr)
    {
    }
    SharedPtr(T data) : data(new T(data)), rc(new std::atomic<int>(1))
    {
    }
    ~SharedPtr()
    {
        if (rc)
        {
            // race condition here?
            --(*rc);
            if (*rc == 0)
            {
                delete data;
                delete rc;
            }
        }
    }
    SharedPtr(const SharedPtr &rhs) : data(rhs.data), rc(rhs.rc)
    {
        // I think this should maybe just increment the reference counter
        // and then return rhs
        (*rc)++;
    }
    SharedPtr &operator=(const SharedPtr &rhs)
    {
        if (this != &rhs)
        {
            // I don't know what to do with the lhs
            this->~SharedPtr(); // TODO is this correct?
            data = rhs.data;
            rc = rhs.rc;
            (*rc)++;
        }
        return *this;
    }
    SharedPtr(SharedPtr &&rhs) noexcept
        : data(std::exchange(rhs.data, nullptr)),
          rc(std::exchange(rhs.rc, nullptr))
    {
    }
    SharedPtr &operator=(SharedPtr &&rhs) noexcept
    {
        if (this != &rhs)
        {
            // Usually here you destruct the lhs object
            // I'm not sure how to do that to a shared pointer

            // Take ownership of objects from rhs
            data = rhs.data;
            rc = rhs.rc;
            // Mutate the rhs into a moved-out object
            rhs.data = nullptr;
            rhs.rc = 0;
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

  private:
    SharedPtr(T data) : data(new T(data)), rc(new std::atomic<int>(1))
    void reset(T *ptr = nullptr) noexcept
    {
        this->~SharedPtr();
        data(ptr);
        rc = new std::atomic<int>(1);
    }

    void swap(SharedPtr& rhs) noexcept
    {
        rhs.data = std::exchange(data, rhs.data);
        rhs.rc = std::exchange(rc, rhs.rc);
    }

#ifdef DEBUG
    void println(const char *variable_name) const
    {
        using namespace std;
        cout << "Dereferencing " << variable_name << " gives " << data;
        if (data)
            cout << " -> " << *data;
        cout << endl;
        cout << "Reference count " << rc;
        if (rc)
            cout << " at " << *rc;
        cout << endl;
    }
#endif
};
} // namespace tomato
