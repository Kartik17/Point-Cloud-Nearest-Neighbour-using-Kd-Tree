#ifndef _COMPARE
#define _COMAPRE
#include "point.h"

template <class T>
struct Comparator{
    size_t sort_dim;
    Comparator(const size_t& d): sort_dim(d){
    }
    
    bool operator ()(const Point<T>& p1, const Point<T>& p2){
        return (p1.get_dim(this->sort_dim) < p2.get_dim(this->sort_dim));
    }
};

#endif
