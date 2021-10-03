
#include <iostream>
#include <string>

namespace ta
{
    void message (const std::string &s1, const std::string &s2, int n);

    void message (const std::string &s1, const std::string &s2);

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
        }

        ~basket_allocator ()
        {
            message ("~basket_allocator", __PRETTY_FUNCTION__);
            std::free (memory_);
        }

        template<typename U, size_t capacity2>
        basket_allocator (const basket_allocator<U, capacity2> &)
        {
            message ("basket_allocator copy", __PRETTY_FUNCTION__);
        }

        T *allocate (std::size_t n)
        {
            if (n > capacity)
                throw std::logic_error ("allocator has no memory");

            if ( memory_ == nullptr )
                alloc_memory ();

            if (n > nb_free_)
                throw std::logic_error ("allocator has no memory");

            message ("allocate", __PRETTY_FUNCTION__, n);

            T *position = memory_ + (capacity - nb_free_);
            assert ( position < memory_ + capacity);

            nb_free_ -= n;
            return position;

        }

        void deallocate ( [[maybe_unused]] T *p, std::size_t n)
        {
            message ("deallocate", __PRETTY_FUNCTION__, n);
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

        void alloc_memory ()
        {
            message ("alloc_memory", __PRETTY_FUNCTION__);
            if ( memory_ != nullptr )
                return;

            void *p = std::malloc (capacity * sizeof (T));
            if (p == nullptr)
                throw std::bad_alloc ();

            memory_ = reinterpret_cast<T*>(p);
            nb_free_ = capacity;
        }

        T* memory_ = nullptr;
        size_t nb_free_ = 0;

    };

}