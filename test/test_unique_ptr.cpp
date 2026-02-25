#include "unique_ptr.hpp"

#define PRINTLN(X) //X.println(#X)

void test_unique_ptr(void)
{
    auto p = tomato::make_unique<int>(4);
    PRINTLN(p);
    // auto q = p;  // compiler error
    auto q = tomato::make_unique<int>(6);
    q = std::move(p);
    PRINTLN(p);
    PRINTLN(q);
    // r = p;       // compiler error
    auto r = std::move(q);
    r = std::move(r);
    PRINTLN(p);
    PRINTLN(q);
    PRINTLN(r);
}

int main(void)
{
    test_unique_ptr();
    return 0;
}
