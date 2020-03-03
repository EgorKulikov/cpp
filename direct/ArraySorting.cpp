#include <bits/stdc++.h>






using namespace std;

template<typename T>
class Vector : public vector<T> {
    using parent = vector<T>;
public:
    Vector() : parent() {}
    explicit Vector(size_t __n) : parent(__n) {}
    Vector(size_t __n, const T& __value) : parent(__n, __value) {}
    explicit Vector(const parent& __x) : parent(__x) {}
    Vector(const Vector& __x) : parent(__x) {}
    Vector(Vector&& __x) noexcept : parent(move(__x)) {}
    Vector(initializer_list<T> __l) : parent(__l) {}
    template<typename _InputIterator, typename = std::_RequireInputIter<_InputIterator>>
    Vector(_InputIterator __first, _InputIterator __last) : parent(__first, __last) {}

    const T& operator[](size_t ind) const {
#ifdef LOCAL
        if (ind >= parent::size()) {
            throw "Out of bounds";
        }
#endif
        return parent::operator[](ind);
    }

    T& operator[](size_t ind) {
#ifdef LOCAL
        if (ind >= parent::size()) {
            throw "Out of bounds";
        }
#endif
        return parent::operator[](ind);
    }

    Vector<T>& operator =(Vector<T>&& __x) noexcept {
        parent::operator=(__x);
        return *this;
    }

    Vector<T>& operator =(const Vector<T>& __x) {
        if (&__x == this) {
            return *this;
        }
        parent::operator=(__x);
        return *this;
    }
};

template<>
class Vector<bool> : public vector<bool> {
    using parent = vector<bool>;
public:
    Vector() : parent() {}
    explicit Vector(size_t __n) : parent(__n) {}
    Vector(size_t __n, const bool& __value) : parent(__n, __value) {}
    explicit Vector(const parent& __x) : parent(__x) {}
    Vector(const Vector& __x) : parent(__x) {}
    Vector(Vector&& __x) noexcept : parent(move(__x)) {}
    Vector(initializer_list<bool> __l) : parent(__l) {}
    template<typename _InputIterator, typename = std::_RequireInputIter<_InputIterator>>
    Vector(_InputIterator __first, _InputIterator __last) : parent(__first, __last) {}

    parent::const_reference operator[](size_t ind) const {
#ifdef LOCAL
        if (ind >= parent::size()) {
            throw "Out of bounds";
        }
#endif
        return parent::operator[](ind);
    }

    parent::reference operator[](size_t ind) {
#ifdef LOCAL
        if (ind >= parent::size()) {
            throw "Out of bounds";
        }
#endif
        return parent::operator[](ind);
    }

    Vector<bool>& operator =(Vector<bool>&& __x) noexcept {
        parent::operator=(__x);
        return *this;
    }

    Vector<bool>& operator =(const Vector<bool>& __x) {
        if (&__x == this) {
            return *this;
        }
        parent::operator=(__x);
        return *this;
    }
};

#ifdef LOCAL
#define vec Vector
#else
#define vec vector
#endif

using vi = vec<int>;


#define all(v) (v).begin(), (v).end()

using ll = long long;
using ld = long double;
using pii = pair<int, int>;

void doReplace() {
}

template <typename T, typename U, typename...Vs>
void doReplace(T& t, const U& u, Vs&&...vs) {
    t = u;
    doReplace(vs...);
}

template <typename T, typename...Us>
T minim(T& was, const T& cand, Us&&...us) {
    if (was > cand) {
        was = cand;
        doReplace(us...);
    }
    return was;
}

template <typename T, typename...Us>
T maxim(T& was, const T& cand, Us&&...us) {
    if (was < cand) {
        was = cand;
        doReplace(us...);
    }
    return was;
}











class NumberIterator : iterator<forward_iterator_tag, int> {
public:
    int v;

    NumberIterator(int v) : v(v) {}

    operator int &() { return v; }

    int operator*() { return v; }
};

class range : pii {
public:
    range(int begin, int end) : pii(begin, max(begin, end)) {}

    range(int n) : pii(0, max(0, n)) {}

    NumberIterator begin() {
        return first;
    }

    NumberIterator end() {
        return second;
    }
};


template <typename T>
class arr {
    T* b;
    int n;
public:
    arr() : arr(0) {}

    arr(int n) : n(n) {
#ifdef LOCAL
        if (n < 0) {
            throw "bad alloc";
        }
#endif
        if (n > 0) {
//            b = (T*) malloc(n * sizeof(T));
            b = new T[n];
        } else {
            b = nullptr;
        }
#ifdef LOCAL
        view();
#endif
    }

    arr(int n, const T& init) : arr(n) {
        if (n > 0) {
            fill(b, b + n, init);
        }
    }
    arr(initializer_list<T> l) : arr(l.size()) {
        if (n > 0) {
            copy(all(l), b);
        }
    }

    arr(T* b, int n) : arr(b, b + n) {}
    arr(T* b, T* e) : b(b), n(e - b) {}

    int size() const {
        return n;
    }

    T* begin() {
        return b;
    }

    const T* begin() const {
        return b;
    }

    T* end() {
        return b + n;
    }

    const T* end() const {
        return b + n;
    }

    arr<T> clone() const {
        arr<T> res(n);
        copy(b, b + n, res.begin());
        return res;
    }

    T& operator[](int at) {
#ifdef LOCAL
        if (at < 0 || at >= n) {
            throw "Out of bounds";
        }
#endif
        return b[at];
    }

    const T& operator[](int at) const {
#ifdef LOCAL
        if (at < 0 || at >= n) {
            throw "Out of bounds";
        }
#endif
        return b[at];
    }

    bool operator ==(const arr& other) const {
        if (n != other.n) {
            return false;
        }
        for (int i : range(n)) {
            if (b[i] != other.b[i]) {
                return false;
            }
        }
        return true;
    }

    vector<T> view() {
        return vector<T>(b, b + min(n, 50));
    }
};

typedef arr<int> arri;

void decreaseByOne() {}

template <typename T, class...Vs>
void decreaseByOne(arr<T>& array, Vs&...vs) {
    int n = array.size();
    for (int i = 0; i < n; ++i) {
        array[i]--;
    }
    decreaseByOne(vs...);
}

template <typename T, typename U>
void decreaseByOne(arr<pair<T, U> >& v) {
    for (auto& p : v) {
        p.first--;
        p.second--;
    }
}


template <typename T>
class arr2d {
    T* b;
    int d1;
    int d2;
    int sz;

public:
    arr2d() : arr2d(0, 0) {}

    arr2d(int d1, int d2) : d1(d1), d2(d2), sz(d1 * d2) {
#ifdef LOCAL
        if (d1 < 0 || d2 < 0) {
            throw "bad alloc";
        }
#endif
        if (sz == 0) {
            b = nullptr;
        } else {
            b = (T*) malloc(sz * sizeof(T));
        }
#ifdef LOCAL
        view();
#endif
    }

    arr2d(int d1, int d2, const T& init) : arr2d(d1, d2) {
        fill(b, b + sz, init);
    }

    arr2d(T* b, int d1, int d2) : b(b), d1(d1), d2(d2), sz(d1 * d2) {}

    int size() const {
        return sz;
    }

    int dim1() const {
        return d1;
    }

    int dim2() const {
        return d2;
    }

    T* begin() {
        return b;
    }

    T* end() {
        return b + sz;
    }

    T& operator()(int i1, int i2) {
#ifdef LOCAL
        if (i1 < 0 || i1 >= d1 || i2 < 0 || i2 >= d2) {
            throw "Out of bounds";
        }
#endif
        return b[i1 * d2 + i2];
    }

    const T& operator()(int i1, int i2) const {
#ifdef LOCAL
        if (i1 < 0 || i1 >= d1 || i2 < 0 || i2 >= d2) {
            throw "Out of bounds";
        }
#endif
        return b[i1 * d2 + i2];
    }

    arr<T> operator[](int at) {
#ifdef LOCAL
        if (at < 0 || at >= d1) {
            throw "Out of bounds";
        }
#endif
        return arr<T>(b + at * d2, d2);
    }

    vector<vector<T>> view() {
        vector<vector<T>> res(min(d1, 50));
        for (int i = 0; i < res.size(); ++i) {
            res[i] = (*this)[i].view();
        }
        return res;
    }

    arr2d<T> clone() {
        arr2d<T> res(d1, d2);
        copy(b, b + sz, res.b);
        return res;
    }
};

template <typename T>
class arr3d {
    T* b;
    int d1;
    int d2;
    int d3;
    int shift;
    int sz;

public:
    arr3d() : arr3d(0, 0, 0) {}

    arr3d(int d1, int d2, int d3) : d1(d1), d2(d2), d3(d3), shift(d2 * d3), sz(d1 * d2 * d3) {
#ifdef LOCAL
        if (d1 < 0 || d2 < 0 || d3 < 0) {
            throw "bad alloc";
        }
#endif
        if (sz == 0) {
            b = nullptr;
        } else {
            b = (T*) malloc(sz * sizeof(T));
        }
#ifdef LOCAL
        view();
#endif
    }

    arr3d(int d1, int d2, int d3, const T& init) : arr3d(d1, d2, d3) {
        fill(b, b + sz, init);
    }

    arr3d(T* b, int d1, int d2, int d3) : b(b), d1(d1), d2(d2), d3(d3), shift(d2 * d3), sz(d1 * d2 * d3) {}

    int size() const {
        return sz;
    }

    int dim1() const {
        return d1;
    }

    int dim2() const {
        return d2;
    }

    int dim3() const {
        return d3;
    }

    T* begin() {
        return b;
    }

    T* end() {
        return b + sz;
    }

    T& operator()(int i1, int i2, int i3) {
#ifdef LOCAL
        if (i1 < 0 || i1 >= d1 || i2 < 0 || i2 >= d2 || i3 < 0 || i3 >= d3) {
            throw "Out of bounds";
        }
#endif
        return b[i1 * shift + i2 * d3 + i3];
    }

    const T& operator()(int i1, int i2, int i3) const {
#ifdef LOCAL
        if (i1 < 0 || i1 >= d1 || i2 < 0 || i2 >= d2 || i3 < 0 || i3 >= d3) {
            throw "Out of bounds";
        }
#endif
        return b[i1 * shift + i2 * d3 + i3];
    }

    arr2d<T> operator[](int at) {
#ifdef LOCAL
        if (at < 0 || at >= d1) {
            throw "Out of bounds";
        }
#endif
        return arr2d<T>(b + at * shift, d2, d3);
    }

    vector<vector<vector<T>>> view() {
        vector<vector<vector<T>>> res(min(d1, 50));
        for (int i = 0; i < res.size(); ++i) {
            res[i] = (*this)[i].view();
        }
        return res;
    }
};

template <typename T>
class arr4d {
    T* b;
    int d1;
    int d2;
    int d3;
    int d4;
    int shift1;
    int shift2;
    int sz;

public:
    arr4d() : arr4d(0, 0, 0, 0) {}

    arr4d(int d1, int d2, int d3, int d4) : d1(d1), d2(d2), d3(d3), d4(d4), shift1(d2 * d3 * d4), shift2(d3 * d4), sz(d1 * d2 * d3 * d4) {
#ifdef LOCAL
        if (d1 < 0 || d2 < 0 || d3 < 0) {
            throw "bad alloc";
        }
#endif
        if (sz == 0) {
            b = nullptr;
        } else {
            b = (T*) malloc(sz * sizeof(T));
        }
#ifdef LOCAL
        view();
#endif
    }

    arr4d(int d1, int d2, int d3, int d4, const T& init) : arr4d(d1, d2, d3, d4) {
        fill(b, b + sz, init);
    }

    arr4d(T* b, int d1, int d2, int d3, int d4) : b(b), d1(d1), d2(d2), d3(d3), d4(d4), shift1(d2 * d3 * d4), shift2(d3 * d4), sz(d1 * d2 * d3 * d4) {
    }

    int size() const {
        return sz;
    }

    int dim1() const {
        return d1;
    }

    int dim2() const {
        return d2;
    }

    int dim3() const {
        return d3;
    }

    int dim4() const {
        return d4;
    }

    T* begin() {
        return b;
    }

    T* end() {
        return b + sz;
    }

    T& operator()(int i1, int i2, int i3, int i4) {
#ifdef LOCAL
        if (i1 < 0 || i1 >= d1 || i2 < 0 || i2 >= d2 || i3 < 0 || i3 >= d3 || i4 < 0 || i4 >= d4) {
            throw "Out of bounds";
        }
#endif
        return b[i1 * shift1 + i2 * shift2 + i3 * d4 + i4];
    }

    const T& operator()(int i1, int i2, int i3, int i4) const {
#ifdef LOCAL
        if (i1 < 0 || i1 >= d1 || i2 < 0 || i2 >= d2 || i3 < 0 || i3 >= d3 || i4 < 0 || i4 >= d4) {
            throw "Out of bounds";
        }
#endif
        return b[i1 * shift1 + i2 * shift2 + i3 * d4 + i4];
    }

    arr3d<T> operator[](int at) {
#ifdef LOCAL
        if (at < 0 || at >= d1) {
            throw "Out of bounds";
        }
#endif
        return arr3d<T>(b + at * shift1, d2, d3, d4);
    }

    vector<vector<vector<vector<T>>>> view() {
        vector<vector<vector<vector<T>>>> res(min(d1, 50));
        for (int i = 0; i < res.size(); ++i) {
            res[i] = (*this)[i].view();
        }
        return res;
    }
};





class ReverseNumberIterator : public NumberIterator {
public:
    ReverseNumberIterator(int v) : NumberIterator(v) {}

    ReverseNumberIterator& operator++() {
        --v;
        return *this;
    }
};

class RevRange : pii {
public:
    RevRange(int begin, int end) : pii(begin - 1, min(begin, end) - 1) {}

    RevRange(int n) : pii(n - 1, min(n, 0) - 1) {}

    ReverseNumberIterator begin() {
        return first;
    }

    ReverseNumberIterator end() {
        return second;
    }
};


using namespace std;

class ArraySorting {
public:
    vector <int> arraySort(vector <int> a) {
        int n = a.size();
        int mx = *max_element(all(a));
        arr2d<int> answer(n + 1, mx + 1);
        fill(all(answer[n]), 0);
        arr2d<int> last(n + 1, mx + 1);
        for (int i : RevRange(n)) {
            int cLast = mx;
            int cVal = answer(i + 1, mx);
            for (int j : RevRange(mx + 1, 1)) {
                if (answer(i + 1, j) <= cVal) {
                    cVal = answer(i + 1, j);
                    cLast = j;
                }
                answer(i, j) = cVal + (j == a[i] ? 0 : 1);
                last(i, j) = cLast;
            }
        }
        int pos = 1;
        int val = answer(0, 1);
        for (int i : range(2, mx + 1)) {
            minim(val, answer(0, i), pos, i);
        }
        for (int i : range(n)) {
            a[i] = pos;
            pos = last(i, pos);
        }
        return a;
    }


// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arr0[] = { 10, 8 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 8 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, arraySort(Arg0)); }
	void test_case_1() { int Arr0[] = { 6, 9 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {6, 9 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, arraySort(Arg0)); }
	void test_case_2() { int Arr0[] = { 9, 8, 10, 4 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 8, 10, 10 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, arraySort(Arg0)); }
	void test_case_3() { int Arr0[] = { 3, 7, 7, 7, 6 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3, 7, 7, 7, 7 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, arraySort(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
    ArraySorting ___test;
    ___test.run_test(-1);
}
// END CUT HERE
