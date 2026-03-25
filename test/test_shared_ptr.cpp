#include "shared_ptr.hpp"

#ifdef DEBUG
#define PRINTLN(X) X.println(#X)
#else
#define PRINTLN(X)
#endif

void test_shared_ptr(void)
{
    auto p = tomato::SharedPtr<int>::make_shared(10);
    PRINTLN(p);
    auto q = p;
    PRINTLN(p);
    PRINTLN(q);
    auto r = std::move(p);
    PRINTLN(p);
    PRINTLN(q);
    PRINTLN(r);
    q = r;
    PRINTLN(p);
    PRINTLN(q);
    PRINTLN(r);
    p = std::move(q);
    PRINTLN(p);
    PRINTLN(q);
    PRINTLN(r);
}

int main(void)
{
    test_shared_ptr();
    return 0;
}
