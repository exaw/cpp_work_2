
#include <cassert>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>

#include "basket_allocator.h"
#include "assoc_list.h"

using namespace std;

int fac (int n)
{
    assert (n >= 0);
    return n == 0 ? 1 : n * fac (n - 1);
}

void demo_1 ()
{
    cout << "=============== demo 1 ===============" << endl;

    map<int, int> m;
    for (int i : {1, 2, 3, 4, 5, 6, 7, 8, 9})
    {
        m.insert ({i, fac (i)});
    }

    for (const auto&[a, b] : m)
    {
        cout << a << ": " << b << endl;
    }

    cout << "--------------------------------------" << endl;

}

void demo_2_1 ()
{
    cout << "=============== demo 2.1 ===============" << endl;

    std::map<int, int, less<int>, ta::basket_allocator<pair<const int, int>, 10>> m;
    for (int i : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9})
    {
        m.insert ({i, fac (i)});
    }

    for (const auto&[a, b] : m)
    {
        cout << a << " " << b << endl;
    }

    cout << "--------------------------------------" << endl;
}

void demo_2_2 ()
{
    cout << "=============== demo 2.2 ===============" << endl;

    std::map<int, int, less<int>, ta::basket_allocator<pair<const int, int>, 10>> m;
    for (int i : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11})
    {
        m.insert ({i, fac (i)});
    }

    for (const auto&[a, b] : m)
    {
        cout << a << " " << b << endl;
    }

    cout << "--------------------------------------" << endl;
}

void demo_3 ()
{
    cout << "=============== demo 3 ===============" << endl;

    ta::assoc_list<string, double, std::allocator<pair<string, int>>> alist;

    for (string s : {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"})
    {
        alist.insert (s, stoi (s));
    }

    for (auto it = alist.begin (); it != alist.end (); it++)
    {
        cout << it->first << ": " << it->second << "    ";
    }
    cout << endl;

    for (string s : {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"})
    {
        cout << s << ": " << alist[s] << "    ";
    }
    cout << endl;
    cout << "--------------------------------------" << endl;

}

void demo_4 ()
{
    cout << "=============== demo 4 ===============" << endl;

    ta::assoc_list<string, double, ta::basket_allocator<pair<string, double>, 40>> alist;

    for (string s : {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"})
    {
        alist.insert (s, stoi (s));
    }

    for (auto it = alist.begin (); it != alist.end (); it++)
    {
        cout << it->first << ": " << it->second << "    ";
    }
    cout << endl;

    for (string s : {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"})
    {
        cout << s << ": " << alist[s] << "    ";
    }
    cout << endl;
    cout << "--------------------------------------" << endl;

}

int main (int, char *[])
{
    try
    {
        demo_1 ();
        demo_2_1 ();
        demo_2_2 ();
        demo_3 ();
        demo_4 ();
    }
    catch (std::exception &e)
    {
        cerr << "std exception: " << e.what () << endl;
    }
    catch (...)
    {
        cerr << "undefined exception: " << endl;
    }

    return 0;

}
