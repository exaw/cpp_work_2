
#include "basket_allocator.h"

#ifndef __PRETTY_FUNCTION__
#include "pretty.h"
#endif

#include <iostream>

//#define USE_PRETTY 1
using namespace std;

namespace ta
{
    void message (const string &s1, const string &s2, int n)
    {
#ifndef USE_PRETTY
        std::cout << s1 << ": [n = " << n << "]" << std::endl;
        (void) s2;
#else
        std::cout << s2 << ": [n = " << n << "]" << std::endl;
        (void)s1;
#endif
    }

    void message (const string &s1, const string &s2)
    {
#ifndef USE_PRETTY
        std::cout << s1 << std::endl;
        (void) s2;
#else
        std::cout << s2 << std::endl;
        (void)s1;
#endif
    }
}
