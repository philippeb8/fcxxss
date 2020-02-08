/*!
    Fornux C++ Superset.

    Copyright (C) 2019  Phil Bouchard <phil@fornux.com>

    Distributed under the Boost Software License, Version 1.0.
    See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt
*/


#ifndef FCXXSS_INCLUDED
#define FCXXSS_INCLUDED


#include <array>
#include <vector>
#include <string>
#include <utility>
#include <stdexcept>
#include <algorithm>
#include <functional>
#include <boost/smart_ptr/root_ptr.hpp>
#include "tinyformat.h"
#include <boost/tti/has_static_member_function.hpp>


extern "C++"
{
    
namespace fcxxss
{
    
inline boost::root_ptr<char> strdup(boost::node_proxy & __y, boost::root_ptr<char> p)
{
    if (p)
        return boost::root_ptr<char>(__y(), "", boost::create<char>().from_range(__y(), p, p + ::strlen(p) + 1));
    else
        throw std::out_of_range(std::string("\"") + p.name() + "\" null pointer");
}

inline boost::root_ptr<wchar_t> wcsdup(boost::node_proxy & __y, boost::root_ptr<wchar_t> p)
{
    if (p)
        return boost::root_ptr<wchar_t>(__y(), "", boost::create<wchar_t>().from_range(__y(), p, p + ::wcslen(p) + 1));
    else
        throw std::out_of_range(std::string("\"") + p.name() + "\" null pointer");
}

inline boost::root_ptr<char> strndup(boost::node_proxy & __y, boost::root_ptr<char> p, std::size_t s)
{
    if (p)
        return boost::root_ptr<char>(__y(), "", boost::create<char>().from_range(__y(), p, p + std::min(::strlen(p) + 1, s)));
    else
        throw std::out_of_range(std::string("\"") + p.name() + "\" null pointer");
}

template <typename... Args>
    inline int asprintf(boost::node_proxy & __y, boost::root_ptr<boost::root_ptr<char>> strp, boost::root_ptr<char> fmt, Args &&... args)
    {
        std::string s = tfm::format(fmt, args...) + '\0';
        
        * strp = new boost::node<char>(s.begin(), s.end());
        
        return s.size() - 1;
    }
    
inline boost::root_ptr<char> memcpy(boost::node_proxy & __y, boost::root_ptr<char> d, boost::root_ptr<char> const s, size_t n)
{
    if (d < s)
    {
        char const * p = s;
        char * q = d;
        
#if defined(__i386__)
        asm volatile ("cld ; movl %3,%0 ; rep ; movsb": "+c" (n), "+S"(p), "+D"(q): "r"(n));
#elif defined(__x86_64__)
        asm volatile ("cld ; movl %3,%%ecx ; rep ; movsb": "+c" (n), "+S"(p), "+D"(q): "r"((uint32_t) (n)));
#else
        while (n--)
            *q++ = *p++;
#endif
    }
    else if (d > s)
    {
        char const * p = s + n - 1;
        char * q = d + n - 1;
        
#if defined(__i386__)
        asm volatile ("std ; movl %3,%0 ; rep ; movsb": "+c" (n), "+S"(p), "+D"(q): "r"(n));
#elif defined(__x86_64__)
        asm volatile ("std ; movl %3,%%ecx ; rep ; movsb": "+c" (n), "+S"(p), "+D"(q): "r"((uint32_t) (n)));
#else
        while (n--)
            *q-- = *p--;
#endif
    }
    
    return d;
}
    
inline boost::root_ptr<char> memset(boost::node_proxy & __y, boost::root_ptr<char> d, char const v, size_t n)
{
    char * q = d;
    
#if defined(__i386__)
    asm volatile ("cld ; movl %3,%0 ; rep ; stosb" : "+c" (n), "+D" (q) : "a" ((unsigned char) v), "r" (n));
#elif defined(__x86_64__)
    asm volatile ("cld ; movl %3,%%ecx ; rep ; stosb" :"+c" (n), "+D" (q) : "a" ((unsigned char) v), "r" ((uint32_t) n));
#else
    while (n--)
        *q++ = v;
#endif
    
    return d;
}

}

}

#endif
