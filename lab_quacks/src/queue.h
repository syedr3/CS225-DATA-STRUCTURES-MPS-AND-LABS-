#pragma once

#define queue libcpp_queue
#include <queue> // use a partial full path so we don't recursively include this file

#undef queue

namespace std {
    template <class T, class Container = deque<T> >
    class queue : public libcpp_queue<T, Container> {
        public:
            static size_t _ctor_count;

            // these are pretty much copied from libc++'s stack header file
            queue() : libcpp_queue<T, Container>() { _ctor_count ++; };
            queue(const queue& q) : libcpp_queue<T, Container>(q) { _ctor_count ++; };
            queue(queue&& q) : libcpp_queue<T, Container>(q) { _ctor_count ++; };

            explicit queue(const Container& c) : libcpp_queue<T, Container>(c) { _ctor_count ++; };
            explicit queue(Container&& c) : libcpp_queue<T, Container>(c) { _ctor_count ++; };

            template <class Alloc> explicit queue(const Alloc& a) : libcpp_queue<T, Container>(a) { _ctor_count ++; };
            template <class Alloc> queue(const Container& c, const Alloc& a) : libcpp_queue<T, Container>(c, a) { _ctor_count ++; };
            template <class Alloc> queue(Container&& c, const Alloc& a) : libcpp_queue<T, Container>(c, a) { _ctor_count ++; };
            template <class Alloc> queue(const queue& c, const Alloc& a) : libcpp_queue<T, Container>(c, a) { _ctor_count ++; };
            template <class Alloc> queue(queue&& c, const Alloc& a) : libcpp_queue<T, Container>(c, a) { _ctor_count ++; };

            queue& operator=(const queue& other) = default;
    };

    template <class T, class Container>
    size_t queue<T, Container>::_ctor_count = 0;
}

/* vim: set ft=cpp: */
