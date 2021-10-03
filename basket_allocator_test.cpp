
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

TEST(test_basket_allocator, test_vector_full_error)
{
    std::vector<int, ta::basket_allocator<int, 10>> v;

    EXPECT_THROW(
            {
                v.push_back (1);
                v.push_back (2);
                v.push_back (3);
                v.push_back (4);
                v.push_back (5);
                v.push_back (6);
                v.push_back (7);
            }, std::exception
            );
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

TEST(test_basket_allocator, test_map_full_error)
{
    std::map<int, int, less<int>, ta::basket_allocator<pair<const int, int>, 10>> m;
    for (int i : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9 })
    {
        m.insert ({i, i*i});
    }
    EXPECT_THROW(
            {
                m.insert ({10, 10*10});
            }, std::exception
    );

    ASSERT_EQ (m.size(), 10);
    for (int i : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9 })
    {
        ASSERT_EQ ( i * i, m[i]);
    }
}

//TEST(test_assoc_list, test_assoc_list_std_alloc)
//{
//    ta::assoc_list<string, int, std::allocator<pair<string, int>>> alist;
//
//    for (string s : {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"})
//    {
//        alist.insert (s, stoi (s));
//    }
//
//    for (string s : {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"})
//    {
//        ASSERT_EQ ( stoi (s), alist[s]);
//    }
//}

TEST(test_assoc_list, test_assoc_list_basket_alloc)
{
    ta::assoc_list<string, double, ta::basket_allocator<pair<string, double>, 40>> alist;

    for (string s : {"0.3", "1.3", "2.3", "3.3", "4.3", "5.3", "6.3", "7.3", "8.3", "9.3"})
    {
        alist.insert (s, stod (s));
    }

    cout << endl;

    for (string s : {"0.3", "1.3", "2.3", "3.3", "4.3", "5.3", "6.3", "7.3", "8.3", "9.3"})
    {
        ASSERT_EQ ( stod (s), alist[s]);
    }
}


int main ()
{
    testing::InitGoogleTest ();
    return RUN_ALL_TESTS ();
}
