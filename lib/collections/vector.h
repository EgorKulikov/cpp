#include "../general.h"

template<typename T>
class Vector : public vector<T> {
public:
    Vector() : vector<T>() {}
    explicit Vector(size_t __n) : vector<T>(__n) {}
    Vector(size_t __n, const T& __value) : vector<T>(__n, __value) {}
    explicit Vector(const vector<T>& __x) : vector<T>(__x) {}
    Vector(const Vector& __x) : vector<T>(__x) {}
    Vector(Vector&& __x) noexcept : vector<T>(std::move(__x)) {}
    Vector(initializer_list<T> __l) : vector<T>(__l) {}
    template<typename _InputIterator, typename = std::_RequireInputIter<_InputIterator>>
    Vector(_InputIterator __first, _InputIterator __last) : vector<T>(__first, __last) {}

    const T& operator[](size_t ind) const {
        return vector<T>::at(ind);
    }

    T& operator[](size_t ind) {
        return vector<T>::at(ind);
    }
};
