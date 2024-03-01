#ifndef FILP_MO201_CALLOCATOR_H
#define FILP_MO201_CALLOCATOR_H

#include <cstdio>
#include <cstdlib>

template <class T>
class CAllocator {
public:
    typedef T value_type;
    typedef size_t size_type;

    CAllocator();
    CAllocator(const CAllocator& other);

    T* allocate(std::size_t n);
    void deallocate(T* p, std::size_t n);

};

#endif //FILP_MO201_CALLOCATOR_H
