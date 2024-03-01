#include "CAllocator.h"

template <class T>
CAllocator<T>::CAllocator() {

}

template<class T>
CAllocator<T>::CAllocator(const CAllocator& other) {

}

template <class T>
T *CAllocator<T>::allocate(size_t count) {
    printf("Allocating %d\n", (int)(count * sizeof(T)));
    return (T*)malloc(sizeof(T) * count);
}

template<class T>
void CAllocator<T>::deallocate(T *V, size_t count) {
    printf("Freeing %d\n", (int)(count * sizeof(T)));
    free(V);
}
