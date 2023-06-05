#pragma once

#define stack libcpp_stack
#include <stack> // use a partial full path so we don't recursively include this file

#undef stack

namespace std {
    template <class T, class Container = deque<T> >
    class stack : public libcpp_stack<T, Container> {
        public: 
            static size_t _ctor_count;

            // these are pretty much copied from libc++'s stack header file
            stack() : libcpp_stack<T, Container>() { _ctor_count ++; };
            stack(const stack& q) : libcpp_stack<T, Container>(q) { _ctor_count ++; };
            stack(stack&& q) : libcpp_stack<T, Container>(q) { _ctor_count ++; };

            explicit stack(const Container& c) : libcpp_stack<T, Container>(c) { _ctor_count ++; };
            explicit stack(Container&& c) : libcpp_stack<T, Container>(c) { _ctor_count ++; };

            template <class Alloc> explicit stack(const Alloc& a) : libcpp_stack<T, Container>(a) { _ctor_count ++; };
            template <class Alloc> stack(const Container& c, const Alloc& a) : libcpp_stack<T, Container>(c, a) { _ctor_count ++; };
            template <class Alloc> stack(Container&& c, const Alloc& a) : libcpp_stack<T, Container>(c, a) { _ctor_count ++; };
            template <class Alloc> stack(const stack& c, const Alloc& a) : libcpp_stack<T, Container>(c, a) { _ctor_count ++; };
            template <class Alloc> stack(stack&& c, const Alloc& a) : libcpp_stack<T, Container>(c, a) { _ctor_count ++; };

            stack& operator=(const stack& other) = default;
    };

    template <class T, class Container>
    size_t stack<T, Container>::_ctor_count = 0;
}

/* vim: set ft=cpp: */
