
namespace ta
{
    template<class InputIt, class T>
    constexpr InputIt find_n (InputIt first, InputIt last, const T &value, int n)
    {
        for (int k = 0; first != last; ++first)
        {
            if (*first == value)
            {
                k += 1;
                if (k == n)
                    return first;
            }
            else
            {
                k = 0;
            }
        }
        return last;
    }
}