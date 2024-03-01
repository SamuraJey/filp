#include "CComparator.h"

// A < B --> true
bool CComparator::operator()(const char* A, const char* B) const {
    while (true) {
        if (A[0] == B[0]) {
            if (!A[0]) return false;
            A++;
            B++;
        } else {
            return A[0] < B[0];
        }
    }
}