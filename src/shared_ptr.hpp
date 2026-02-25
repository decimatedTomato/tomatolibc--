#include <atomic>
#include <utility>

namespace tomato
{
template <typename T> class SharedPtr
{
  private:
    T   *data;
    std::atomic<int> *rc;

  public:
    static SharedPtr make_shared(T data)
    {
        SharedPtr ret(data);
        return ret;
    }
    ~SharedPtr()
    {
        if (rc)
        {
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

    T operator*() const noexcept
    {
        return *data;
    }

    T get() const noexcept
    {
        return *data;
    }

  private:
    SharedPtr(T data) : data(new T(data)), rc(new std::atomic<int>(1))
    {
    }
};
} // namespace tomato