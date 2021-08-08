
#include <map>
#include <vector>

#include <gtest/gtest.h>

#include "basket_allocator.h"
#include "assoc_list.h"

using namespace std;

TEST(test_basket_allocator, test_vector)
{
    std::vector<int, ta::basket_allocator<int, 100>> v;
    v.push_back (1);
    v.push_back (2);
    v.push_back (3);
    v.push_back (4);
    v.push_back (5);
    v.push_back (6);

    ASSERT_EQ (v.size(), 6);
    for ( int i : {0, 1, 2, 3, 4, 5})
    {
        ASSERT_EQ ( i+1, v[i]);
    }
}

TEST(test_basket_allocator, test_vector_error)
{
//    std::vector<int, ta::basket_allocator<int, 20>> v;
//    v.push_back (1);
//    v.push_back (2);
//    v.push_back (3);
//    v.push_back (4);
//    v.push_back (5);
//    v.push_back (6);
//
//    ASSERT_EQ (v.size(), 6);
//    for ( int i : {0, 1, 2, 3, 4, 5})
//    {
//        ASSERT_EQ ( i+1, v[i]);
//    }
}

TEST(test_basket_allocator, test_map)
{
    std::map<int, int, less<int>, ta::basket_allocator<pair<const int, int>, 10>> m;
    for (int i : {0, 1, 2, 3, 4})
    {
        m.insert ({i, i*i});
    }

    ASSERT_EQ (m.size(), 5);
    for ( int i : {0, 1, 2, 3, 4})
    {
        ASSERT_EQ ( i * i, m[i]);
    }
}

int main ()
{
    testing::InitGoogleTest ();
    return RUN_ALL_TESTS ();
}
