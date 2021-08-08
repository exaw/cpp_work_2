
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "find_n.h"

namespace ta
{
    void message (const std::string &s1, const std::string &s2, int n);

    void message (const std::string &s1, const std::string &s2);

    enum class Mark
    {
        Free, Used
    };

    template<typename T, size_t capacity>
    struct basket_allocator
    {
        using value_type = T;

        template<typename U>
        struct rebind
        {
            using other = basket_allocator<U, capacity>;
        };

        basket_allocator ()
        {
            message ("basket_allocator", __PRETTY_FUNCTION__);
            add_basket ();
        }

        ~basket_allocator ()
        {
            message ("~basket_allocator", __PRETTY_FUNCTION__);
            for (auto &basket : baskets_)
                std::free (basket);
        }

        template<typename U, size_t capacity2>
        basket_allocator (const basket_allocator<U, capacity2> &)
        {
            message ("basket_allocator copy", __PRETTY_FUNCTION__);
        }

        T *allocate (std::size_t n)
        {
            message ("allocate", __PRETTY_FUNCTION__, n);

            if (n > capacity)
                throw std::logic_error ("allocator has no memory");

            T *position = find_free_position (n);
            if (position != nullptr)
            {
                return position;
            }
            else
            {
                add_basket ();
                std::fill_n (begin (marks_.back ()), n, Mark::Used);
                T *position = baskets_.back ();
                return position;
            }
        }

        void deallocate (T *p, std::size_t n)
        {
            message ("deallocate", __PRETTY_FUNCTION__, n);
            auto[basket, position] = find_position (p);
            std::fill_n (begin (marks_[basket]) + position, n, Mark::Free);
        }

        template<typename U, typename ...Args>
        void construct (U *p, Args &&...args)
        {
            message ("construct", __PRETTY_FUNCTION__);
            new (p) U (std::forward<Args> (args)...);
        }

        template<typename U>
        void destroy (U *p)
        {
            message ("destroy", __PRETTY_FUNCTION__);
            p->~U ();
        }

    private:

        void add_basket ()
        {
            message ("add_basket", __PRETTY_FUNCTION__);
            void *p = std::malloc (capacity * sizeof (T));
            if (p == nullptr)
                throw std::bad_alloc ();

            T *t = reinterpret_cast<T *>(p);

            baskets_.push_back (t);
            marks_.push_back (std::vector<Mark> (capacity, Mark::Free));
        }

        T *find_free_position (std::size_t n)
        {
            for (size_t i = 0; i < marks_.size (); i++)
            {
                auto &marks = marks_[i];
                auto freeIt = ta::find_n (begin (marks), end (marks), Mark::Free, n);
                if (freeIt != end (marks))
                {
                    int start = distance (begin (marks), freeIt);
                    std::fill_n (begin (marks) + start, n, Mark::Used);
                    return baskets_[i] + start;
                }
            }

            return nullptr;
        }

        std::pair<size_t, size_t> find_position (T *p)
        {
            int minDist = std::numeric_limits<int>::max ();
            size_t needPool = 0;
            for (size_t i = 0; i < baskets_.size (); i++)
            {
                //int dist = distance (baskets_[i], p);
                int dist = p - baskets_[i];
                if (dist >= 0)
                    if (dist < minDist)
                    {
                        minDist = dist;
                        needPool = i;
                    }
            }

            return {needPool, minDist};
        }

        std::vector<T *> baskets_;
        std::vector<std::vector<Mark>> marks_;
    };

}