#include <iostream>
#include <utility>

using std::cout;
using std::endl;

namespace tomato {
template<typename T>
class SharedPtr
{
private:
    T *data;
    int *rc;
public:
    static SharedPtr make_shared(T data)
    {
        SharedPtr ret(data);
        cout << "Making shared pointer to data " << data << " at address "
            << ret.data << endl;
        cout << "Reference count is at " << *ret.rc << endl;
        return ret;
    }
    ~SharedPtr()
    {
        if (rc)
        {
            --(*rc);
            cout << "Reference count falls to " << *rc << endl;
            if (*rc == 0)
            {
                cout << "Deleting from pointer " << data;
                if (data) cout << " -> " << *data;
                cout << endl;
                delete data;
                delete rc;
            }
        }
    }
    SharedPtr(const SharedPtr& rhs)
    : data(rhs.data)
    , rc(rhs.rc)
    {
        // I think this should maybe just increment the reference counter
        // and then return rhs
        (*rc)++;
        cout << "Copied data " << data << " to " << rhs.data
            << " and reference count " << *rc << " from " << rc << " to " << rhs.rc << endl;
        cout << "Incremented reference count" << endl;
    }
    SharedPtr& operator=(const SharedPtr& rhs)
    {
        if (this != &rhs)
        {
            // I don't know what to do with the lhs
            this->~SharedPtr();    // TODO is this correct?
            data = rhs.data;
            rc = rhs.rc;
            (*rc)++;
            cout << "Copied data " << data << " to " << rhs.data
            << " and reference count " << *rc << " from " << rc << " to " << rhs.rc << endl;
            cout << "Incremented reference count" << endl;
        }
        return *this;
    }
    SharedPtr(SharedPtr&& rhs) noexcept
    : data(std::exchange(rhs.data, nullptr))
    , rc(std::exchange(rhs.rc, nullptr))
    {
        cout << "Exchanged data and reference count between this and rhs in initializer list" << endl;
    }
    SharedPtr& operator=(SharedPtr&& rhs) noexcept
    {
        if (this != &rhs)
        {
            cout << "Moving data " << *rhs.data << " from " << rhs.data << " to " << data << endl;
            // Usually here you destruct the lhs object
            // I'm not sure how to do that to a shared pointer
            
            // Take ownership of objects from rhs
            data = rhs.data;
            rc = rhs.rc;
            // Mutate the rhs into a moved-out object
            rhs.data = nullptr;
            rhs.rc = 0;
        }
        else
        {
            cout << "Moving object into itself did nothing" << endl;
        }
        return *this;
    }
    
    T operator *() const
    {
        if (!data) throw "Tried to dereference moved out Shared_ptr";
        return *data;
    }

    T get() const
    {
        if (!data) throw "Tried to dereference moved out Shared_ptr";
        return *data;
    }

    void println(const char *variable_name) const
    {
        cout << "Dereferencing " << variable_name << " gives " << data;
        if (data) cout << " -> " << get();
        cout << endl;
        cout << "Reference count " << rc;
        if (rc) cout << " at " << *rc;
        cout << endl;
    }

    private:
    SharedPtr(T data)
    : data(new T(data))
    , rc(new int(1))
    {}
};
} // namespace tomato