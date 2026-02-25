#include <iostream>
#include <utility>

using std::cout;
using std::endl;

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
        cout << "Making unique pointer to data " << data << " at address " << ret.data << endl;
        return ret;
    }
    ~UniquePtr()
    {
        cout << "Deleting from pointer " << data;
        if (data) cout << " -> " << *data;
        cout << endl;
        delete data;
    }
    UniquePtr(const UniquePtr&) = delete;   // unique_ptr should not be copyable
    UniquePtr(UniquePtr&& rhs) noexcept
    : data(std::exchange(rhs.data, nullptr))
    {
        cout << "Exchanged data between this and rhs in initializer list" << endl;
    }
    UniquePtr& operator=(UniquePtr&& rhs) noexcept
    {
        if (this != &rhs)
        {
            cout << "Moving data " << *rhs.data << " from " << rhs.data << " to " << data << endl;
            // Free data from this
            delete data;
            // Take ownership of objects from rhs
            data = rhs.data;
            // Mutate the rhs into a moved-out object
            rhs.data = nullptr;
        }
        else
        {
            cout << "Moving object into itself did nothing" << endl;
        }
        return *this;
    }

    T operator *() const
    {
        if (!data) throw "Tried to dereference moved out Unique_ptr";
        return *data;
    }


    T get() const
    {
        if (!data) throw "Tried to dereference moved out Unique_ptr";
        return *data;
    }

    void println(const char *variable_name) const
    {
        cout << "Dereferencing " << variable_name << " gives " << data;
        if (data) cout << " -> " << get();
        cout << endl;
    }
    
    private:
    UniquePtr(T data)
    : data(new T(data))
    {}
};
} // namespace tomato
