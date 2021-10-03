
#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace ta
{
    template<typename T, typename U>
    struct assoc_list_node
    {
        assoc_list_node () = default;

        assoc_list_node (const T &key, const U &value) : item (key, value)
        {};

        std::pair<T, U> item;
        assoc_list_node<T, U> *next = nullptr;
    };

    template<typename Key, typename T>
    struct assoc_list_iterator
    {
        typedef assoc_list_iterator<Key, T> iterator_t;

        assoc_list_iterator () = default;

        assoc_list_iterator (assoc_list_node<Key, T> *node) : node_ (node)
        {}

        iterator_t &operator++ ()
        {
            node_ = node_->next;
            return *this;
        }

        iterator_t operator++ (int)
        {
            auto tmp = *this;
            node_ = node_->next;
            return tmp;
        }

        std::pair<Key, T> &operator* ()
        { return node_->item; }

        const std::pair<Key, T> &operator* () const
        { return node_->item; }

        std::pair<Key, T> *operator-> ()
        { return &node_->item; }

        const std::pair<Key, T> *operator-> () const
        { return &node_->item; }

        assoc_list_node<Key, T> *node_ = nullptr;

        friend bool operator!= (const iterator_t &t1, const iterator_t &t2)
        { return t1.node_ != t2.node_; }
    };

    template<typename Key, typename T, typename Alloc>
    class assoc_list
    {
        typedef typename __gnu_cxx::__alloc_traits<Alloc>::template
        rebind<assoc_list_node<Key, T>>::other node_alloc_t;

        typedef assoc_list_node<Key, T> node_t;
        typedef assoc_list_iterator<Key, T> iterator_t;

    public:

        assoc_list ()
        {
            last_ = new node_t;
            first_ = last_;
        }

        assoc_list (const assoc_list &) = delete;

        assoc_list (const assoc_list &&) = delete;

        assoc_list &operator= (const assoc_list &) = delete;

        assoc_list &operator= (const assoc_list &&) = delete;

        ~assoc_list ()
        {
            for (auto it = first_; it != last_; it = it->next)
            {
                delete_node (it);
            }

            delete_node (last_);

        }

        iterator_t begin ()
        {
            return iterator_t (first_);
        }

        iterator_t end ()
        {
            return iterator_t (last_);
        }

        void insert (const Key &key, const T &value)
        {
            for (auto it = begin (); it != end (); it++)
            {
                if (it->first == key)
                {
                    it->second = value;
                    return;
                }
            }

            auto node = alloc_.allocate (1);
            alloc_.construct (node, key, value);

            node->next = first_;
            first_ = node;

        }

        T &operator[] (const Key &key)
        {
            for (auto it = begin (); it != end (); it++)
            {
                if (it->first == key)
                    return it->second;
            }

            throw std::logic_error ("assoc_list bad key");
        }

        const T &operator[] (const Key &key) const
        {
            for (auto it = begin (); it != end (); it++)
            {
                if (it->first == key)
                    return it->second;
            }

            throw std::logic_error ("assoc_list bad key");
        }

    private:

        void delete_node (node_t *node)
        {
            alloc_.destroy (node);
            alloc_.deallocate (node, 1);
        }

        node_t *first_ = nullptr;
        node_t *last_ = nullptr;
        node_alloc_t alloc_;
    };
}