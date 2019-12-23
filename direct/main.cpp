#include <bits/stdc++.h>

using namespace std;

template<typename T>
class Vector : public vector<T> {
    using parent = vector<T>;
public:
    Vector() : parent() {}

    explicit Vector(size_t __n) : parent(__n) {}

    Vector(size_t __n, const T &__value) : parent(__n, __value) {}

    explicit Vector(const parent &__x) : parent(__x) {}

    Vector(const Vector &__x) : parent(__x) {}

    Vector(Vector &&__x) noexcept : parent(move(__x)) {}

    Vector(initializer_list<T> __l) : parent(__l) {}

    template<typename _InputIterator, typename = std::_RequireInputIter<_InputIterator>>
    Vector(_InputIterator __first, _InputIterator __last) : parent(__first, __last) {}

    const T &operator[](size_t ind) const {
#ifdef LOCAL
        if (ind >= parent::size()) {
            throw "Out of bounds";
        }
#endif
        return *(parent::_M_impl._M_start + ind);
    }

    T &operator[](size_t ind) {
#ifdef LOCAL
        if (ind >= parent::size()) {
            throw "Out of bounds";
        }
#endif
        return *(parent::_M_impl._M_start + ind);
    }

    Vector<T> &operator=(Vector<T> &&__x) noexcept {
        parent::operator=(__x);
        return *this;
    }

    Vector<T> &operator=(const Vector<T> &__x) {
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

    Vector(size_t __n, const bool &__value) : parent(__n, __value) {}

    explicit Vector(const parent &__x) : parent(__x) {}

    Vector(const Vector &__x) : parent(__x) {}

    Vector(Vector &&__x) noexcept : parent(move(__x)) {}

    Vector(initializer_list<bool> __l) : parent(__l) {}

    template<typename _InputIterator, typename = std::_RequireInputIter<_InputIterator>>
    Vector(_InputIterator __first, _InputIterator __last) : parent(__first, __last) {}

    parent::const_reference operator[](size_t ind) const {
#ifdef LOCAL
        if (ind >= parent::size()) {
            throw "Out of bounds";
        }
#endif
        return *const_iterator(this->_M_impl._M_start._M_p
                               + ind / int(_S_word_bit), ind % int(_S_word_bit));
    }

    parent::reference operator[](size_t ind) {
#ifdef LOCAL
        if (ind >= parent::size()) {
            throw "Out of bounds";
        }
#endif
        return *iterator(this->_M_impl._M_start._M_p
                         + ind / int(_S_word_bit), ind % int(_S_word_bit));
    }

    Vector<bool> &operator=(Vector<bool> &&__x) noexcept {
        parent::operator=(__x);
        return *this;
    }

    Vector<bool> &operator=(const Vector<bool> &__x) {
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
using pii = pair<int, int>;

const double PI = atan(1) * 4;

template<typename T>
T minim(T &was, T cand) {
    return was = min(was, cand);
}

template<typename T>
class arr {
    T *b;
    T *e;
    int n;
public:
    arr() : b(nullptr), e(nullptr), n(0) {}

    arr(int n) : n(n) {
#ifdef LOCAL
        if (n < 0) {
            throw "bad alloc";
        }
#endif
        if (n > 0) {
            b = new T[n];
            e = b + n;
        } else {
            b = e = nullptr;
        }
    }

    arr(int n, const T &init) : n(n) {
#ifdef LOCAL
        if (n < 0) {
            throw "bad alloc";
        }
#endif
        if (n > 0) {
            b = new T[n];
            e = b + n;
            fill(b, e, init);
        } else {
            b = e = nullptr;
        }
    }

    arr(initializer_list<T> l) : n(l.size()) {
        if (n == 0) {
            b = e = nullptr;
        } else {
            b = new T[l.size()];
            e = b + n;
            copy(all(l), b);
        }
    }

    arr(T *b, int n) : b(b), e(b + n), n(n) {}

    arr(T *b, T *e) : b(b), e(e), n(e - b) {}

    size_t size() const {
        return n;
    }

    T *begin() {
        return b;
    }

    T *end() {
        return e;
    }

    arr<T> clone() const {
        arr<T> res(n);
        copy(b, e, res.begin());
        return res;
    }

    T &operator[](int at) {
#ifdef LOCAL
        if (at < 0 || at >= n) {
            throw "Out of bounds";
        }
#endif
        return b[at];
    }

    const T &operator[](int at) const {
#ifdef LOCAL
        if (at < 0 || at >= n) {
            throw "Out of bounds";
        }
#endif
        return b[at];
    }

    void swap(arr<T> &arr) {
        std::swap(b, arr.b);
        std::swap(e, arr.e);
        std::swap(n, arr.n);
    }
};

typedef arr<int> arri;

void decreaseByOne() {}

template<typename T, class...Vs>
void decreaseByOne(arr<T> &array, Vs &...vs) {
    int n = array.size();
    for (int i = 0; i < n; ++i) {
        array[i]--;
    }
    decreaseByOne(vs...);
}

template<typename T, typename U>
void decreaseByOne(arr<pair<T, U> > &v) {
    for (auto &p : v) {
        p.first--;
        p.second--;
    }
}

inline bool isWhitespace(int c) {
    return isspace(c) || c == EOF;
}

class Input {
private:
    istream &in;
    bool exhausted = false;

    inline int get() {
        if (exhausted) {
#ifdef LOCAL
            throw "Input exhausted";
#endif
            return EOF;
        }
        int c = in.get();
        if (c == EOF) {
            exhausted = true;
        }
        return c;
    }

    template<typename T>
    inline T readInteger() {
        skipWhitespace();
        int c = get();
        int sgn = 1;
        if (c == '-') {
            sgn = -1;
            c = get();
        }
        T res = 0;
        do {
            if (!isdigit(c)) {
#ifdef LOCAL
                throw "Number format error";
#endif
                return sgn * res;
            }
            res *= 10;
            res += c - '0';
            c = get();
        } while (!isWhitespace(c));
        return res * sgn;
    }

    void initArrays(int) {}

    template<typename T, class...Vs>
    void initArrays(int n, arr<T> &array, Vs &...vs) {
        array = arr<T>(n);
        initArrays(n, vs...);
    }

    void readImpl(int) {}

    template<typename T, class...Vs>
    void readImpl(int i, arr<T> &arr, Vs &...vs) {
        arr[i] = readType<T>();
        readImpl(i, vs...);
    }

public:
    Input(istream &in) : in(in) {};

    inline void skipWhitespace() {
        int c;
        while (isWhitespace(c = in.peek()) && c != EOF) {
            in.get();
        }
        if (c == EOF) {
            exhausted = true;
        }
    }

    inline int readInt() {
        return readInteger<int>();
    }

    ll readLong() {
        return readInteger<ll>();
    }

    string readString() {
        skipWhitespace();
        int c = get();
        if (c == EOF) {
#ifdef LOCAL
            throw "Input exhausted";
#endif
            return "";
        }
        vec<char> res;
        do {
            res.push_back(c);
        } while (!isWhitespace(c = get()));
        return string(all(res));
    }

    arri readIntArray(int size) {
        return readArray<int>(size);
    }

    template<typename T>
    T readType() {
        throw "Operation not supported";
    }

    template<typename U, typename V>
    pair<U, V> readType() {
        U first = readType<U>();
        V second = readType<V>();
        return make_pair(first, second);
    }

    template<typename T>
    arr<T> readArray(int n) {
        arr<T> res(n);
        for (int i = 0; i < n; i++) {
            res[i] = readType<T>();
        }
        return res;
    }


    template<class...Vs>
    void readArrays(int n, Vs &...vs) {
        initArrays(n, vs...);
        for (int i = 0; i < n; i++) {
            readImpl(i, vs...);
        }
    }

    template<typename U, typename V>
    arr<pair<U, V> > readArray(int n) {
        arr<pair<U, V> > res(n);
        for (int i = 0; i < n; i++) {
            res[i] = readType<U, V>();
        }
        return res;
    }

    string readLine() {
        int c = get();
        if (c == EOF) {
#ifdef LOCAL
            throw "Input exhausted";
#endif
            return "";
        }
        vec<char> res;
        do {
            res.push_back(c);
            c = get();
        } while (c != '\n' && c != '\r' && c != EOF);
        return string(all(res));
    }

    char readChar() {
        skipWhitespace();
        int c = get();
        if (c == EOF) {
#ifdef LOCAL
            throw "Input exhausted";
#endif
            return 0;
        }
        return c;
    }

    bool isExhausted() { return exhausted; }
};

template<>
int Input::readType() {
    return readInt();
}

template<>
ll Input::readType() {
    return readLong();
}

template<>
char Input::readType() {
    return readChar();
}

template<>
string Input::readType() {
    return readString();
}


class Output {
private:
    ostream &out;

    template<typename T>
    void printSingle(const T &value) {
        out << value;
    }

    template<typename T>
    void printSingle(const vec<T> &array) {
        size_t n = array.size();
        for (int i = 0; i < n; ++i) {
            out << array[i];
            if (i + 1 != n) {
                out << ' ';
            }
        }
    }

    template<typename T>
    void printSingle(const arr<T> &array) {
        size_t n = array.size();
        for (int i = 0; i < n; ++i) {
            out << array[i];
            if (i + 1 != n) {
                out << ' ';
            }
        }
    }

    template<typename T, typename U>
    void printSingle(const pair<T, U> &value) {
        out << value.first << ' ' << value.second;
    }

public:
    Output(ostream &out) : out(out) {
        out << fixed << setprecision(20);
    }

    void print() {}

    template<typename T, typename...Targs>
    void print(const T &first, const Targs... args) {
        printSingle(first);
        if (sizeof...(args) != 0) {
            out << ' ';
            print(args...);
        }
    }

    template<typename...Targs>
    void printLine(const Targs... args) {
        print(args...);
        out << '\n';
    }

    void flush() {
        out.flush();
    }
};


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


template<typename T>
class Matrix {
private:
    int rows;
    int cols;
    T *data;

    void powerImpl(Matrix<T> &result, Matrix<T> &temp, ll exponent) const;

public:
    Matrix(int rows = 0, int cols = 0) : rows(rows), cols(cols) {
        data = new T[rows * cols];
    }

    T *operator[](int row) {
        return data + (row * cols);
    }

    const T *operator[](int row) const {
        return data + (row * cols);
    }

//    Matrix<T>& power(ll exponent) const;

    void makeOne() {
        fill(data, data + (rows * cols), 0);
        for (int i = 0; i < rows; i++) {
            data[i * cols + i] = 1;
        }
    }

    template<typename U>
    friend void multiply(Matrix<U> &c, const Matrix<U> &a, const Matrix<U> &b);
};

template<typename T>
void multiply(Matrix<T> &c, const Matrix<T> &a, const Matrix<T> &b) {
    fill(c.data, c.data + c.rows * c.cols, 0);
    for (int i = 0; i < c.rows; i++) {
        int atC = i * c.cols;
        int atA = i * a.cols;
        for (int j = 0; j < b.rows; j++) {
            int atB = j * b.cols;
            for (int k = 0; k < c.cols; k++) {
                c.data[atC + k] += a.data[atA + j] * b.data[atB + k];
            }
        }
    }
}

/*template<typename T>
Matrix<T>& Matrix<T>::power(ll exponent) const {
    if (temp == nullptr) {
        temp = new Matrix<T>(rows, cols);
    }
    if (res == nullptr) {
        res = new Matrix<T>(rows, cols);
    }
//    Matrix<T> result(rows, cols);
//    Matrix<T> temp(rows, cols);
    powerImpl(*res, *temp, exponent);
    return *res;
}*/

template<typename T>
void Matrix<T>::powerImpl(Matrix<T> &result, Matrix<T> &temp, ll exponent) const {
    if (exponent == 0) {
        fill(result.data, result.data + rows * cols, 0);
        for (int i = 0; i < rows; i++) {
            result[i][i] = 1;
        }
    } else if ((exponent & 1) == 1) {
        powerImpl(temp, result, exponent - 1);
        multiply(result, temp, *this);
    } else {
        powerImpl(temp, result, exponent >> 1);
        multiply(result, temp, temp);
    }
}


const int MOD7 = 1000000007;
const int MOD9 = 1000000009;
const int MODF = 998244353;

int mod = MOD7;

template<typename T>
T gcd(T a, T b, T &x, T &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    int d = gcd(b % a, a, y, x);
    x -= (b / a) * y;
    return d;
}

class modint {
public:
    int n;

    modint() : n(0) {}

    modint(ll n) {
        if (n >= 0 && n < mod) {
            this->n = n;
            return;
        }
        n %= mod;
        if (n < 0) {
            n += mod;
        }
        this->n = n;
    }

    modint &operator+=(const modint &other) {
        n += other.n;
        if (n >= mod) {
            n -= mod;
        }
        return *this;
    }

    modint &operator-=(const modint &other) {
        n -= other.n;
        if (n < 0) {
            n += mod;
        }
        return *this;
    }

    modint &operator*=(const modint &other) {
        n = ll(n) * other.n % mod;
        return *this;
    }

    modint operator-() {
        if (n == 0) {
            return 0;
        }
        return modint(mod - n);
    }

    modint inverse() {
        ll x, y;
        gcd(ll(n), ll(mod), x, y);
        return x;
    }
};

modint operator+(const modint &a, const modint &b) {
    return modint(a) += b;
}

modint operator-(const modint &a, const modint &b) {
    return modint(a) -= b;
}

modint operator*(const modint &a, const modint &b) {
    return modint(a) *= b;
}

ostream &operator<<(ostream &out, const modint &val) {
    return out << val.n;
}

bool operator==(const modint &a, const modint &b) {
    return a.n == b.n;
}

bool operator!=(const modint &a, const modint &b) {
    return a.n != b.n;
}


template<typename W, typename C>
class WeightedFlowEdge {
private:
    WeightedFlowEdge<W, C> *reverseEdge;

public:
    const int from;
    const int to;
    W weight;
    C capacity;
    int id;

    WeightedFlowEdge(int from, int to, W weight, C capacity) : from(from), to(to), weight(weight), capacity(capacity) {
        reverseEdge = new WeightedFlowEdge(this);
    }

    WeightedFlowEdge<W, C> *transposed() { return nullptr; }

    WeightedFlowEdge<W, C> *reverse() { return reverseEdge; }

    void push(C flow) {
        capacity -= flow;
        reverseEdge->capacity += flow;
    }

    C flow() const {
        return reverseEdge->capacity;
    }

private:
    WeightedFlowEdge(WeightedFlowEdge<W, C> *reverse) : from(reverse->to), to(reverse->from), weight(-reverse->weight),
                                                        capacity(0) {
        reverseEdge = reverse;
    }
};

template<typename C>
class FlowEdge {
private:
    FlowEdge<C> *reverseEdge;

public:
    const int from;
    const int to;
    C capacity;
    int id;

    FlowEdge(int from, int to, C capacity) : from(from), to(to), capacity(capacity) {
        reverseEdge = new FlowEdge(this);
    }

    FlowEdge<C> *transposed() { return nullptr; }

    FlowEdge<C> *reverse() { return reverseEdge; }

    void push(C flow) {
        capacity -= flow;
        reverseEdge->capacity += flow;
    }

    C flow() const {
        return reverseEdge->capacity;
    }

private:
    FlowEdge(FlowEdge<C> *reverse) : from(reverse->to), to(reverse->from), capacity(0) {
        reverseEdge = reverse;
    }
};

template<typename W>
class WeightedEdge {
public:
    const int from;
    const int to;
    W weight;
    int id;

    WeightedEdge(int from, int to, W weight) : from(from), to(to), weight(weight) {
    }

    WeightedEdge<W> *transposed() { return nullptr; }

    WeightedEdge<W> *reverse() { return nullptr; }
};

template<typename W>
class BiWeightedEdge {
private:
    BiWeightedEdge<W> *transposedEdge;

public:
    const int from;
    const int to;
    W weight;
    int id;

    BiWeightedEdge(int from, int to, W weight) : from(from), to(to), weight(weight) {
        transposedEdge = new BiWeightedEdge(this);
    }

    BiWeightedEdge<W> *transposed() { return transposedEdge; }

    BiWeightedEdge<W> *reverse() { return nullptr; }

private:
    BiWeightedEdge(BiWeightedEdge<W> *transposed) : from(transposed->to), to(transposed->from),
                                                    weight(transposed->weight) {
        transposedEdge = transposed;
    }
};

class BaseEdge {
public:
    const int from;
    const int to;
    int id;

    BaseEdge(int from, int to) : from(from), to(to) {
    }

    BaseEdge *transposed() { return nullptr; }

    BaseEdge *reverse() { return nullptr; }
};

class BiEdge {
private:
    BiEdge *transposedEdge;

public:
    const int from;
    const int to;
    int id;

    BiEdge(int from, int to) : from(from), to(to) {
        transposedEdge = new BiEdge(this);
    }

    BiEdge *transposed() { return transposedEdge; }

    BiEdge *reverse() { return nullptr; }

private:
    BiEdge(BiEdge *transposed) : from(transposed->to), to(transposed->from) {
        transposedEdge = transposed;
    }
};

template<class Edge>
class Graph {
public:
    int vertexCount;
    int edgeCount = 0;
private:
    arr<vec<Edge *> > edges;

public:
    Graph(int vertexCount) : vertexCount(vertexCount), edges(vertexCount, vec<Edge *>()) {}

    void addEdge(Edge *edge) {
        edge->id = edgeCount;
        edges[edge->from].push_back(edge);
        Edge *reverse = edge->reverse();
        if (reverse != nullptr) {
            reverse->id = edgeCount;
            edges[reverse->from].push_back(reverse);
        }
        Edge *transposed = edge->transposed();
        if (transposed != nullptr) {
            edges[transposed->from].push_back(transposed);
            transposed->id = edgeCount;
            Edge *transRev = transposed->reverse();
            if (transRev != nullptr) {
                edges[transRev->from].push_back(transRev);
                transRev->id = edgeCount;
            }
        }
        edgeCount++;
    }

    template<typename...Ts>
    void addEdge(Ts...args) {
        addEdge(new Edge(args...));
    }

    vec<Edge *> &operator[](int at) {
        return edges[at];
    }
};


template<typename Value, typename Delta>
class SegmentTree {
    const int size;
    const Value defaultValue;
    const Delta defaultDelta;
    function<Value(Value, Value)> joinValue;
    function<Delta(Delta, Delta)> joinDelta;
    function<Value(Value, Delta, int, int)> accumulate;
    arr<Value> value;
    arr<Delta> delta;

    void init(int root, int left, int right) {
        if (left + 1 == right) {
            value[root] = defaultValue;
        } else {
            int mid = (left + right) >> 1;
            init(2 * root + 1, left, mid);
            init(2 * root + 2, mid, right);
            value[root] = joinValue(value[2 * root + 1], value[2 * root + 2]);
        }
    }

    void apply(int root, Delta dlt, int left, int right) {
        value[root] = accumulate(value[root], dlt, left, right);
        delta[root] = joinDelta(delta[root], dlt);
    }

    void pushDown(int root, int left, int mid, int right) {
        apply(2 * root + 1, delta[root], left, mid);
        apply(2 * root + 2, delta[root], mid, right);
        delta[root] = defaultDelta;
    }

    void update(int root, int left, int right, int from, int to, Delta dlt) {
        if (left >= from && right <= to) {
            apply(root, dlt, left, right);
            return;
        }
        if (right <= from || left >= to) {
            return;
        }
        int mid = (left + right) >> 1;
        pushDown(root, left, mid, right);
        update(2 * root + 1, left, mid, from, to, dlt);
        update(2 * root + 2, mid, right, from, to, dlt);
        value[root] = joinValue(value[2 * root + 1], value[2 * root + 2]);
    }

    Value query(int root, int left, int right, int from, int to) {
        if (left >= from && right <= to) {
            return value[root];
        }
        if (right <= from || left >= to) {
            return defaultValue;
        }
        int mid = (left + right) >> 1;
        pushDown(root, left, mid, right);
        return joinValue(query(2 * root + 1, left, mid, from, to), query(2 * root + 2, mid, right, from, to));
    }

public:
    SegmentTree(int size, function<Value(Value, Value)> joinValue,
                function<Delta(Delta, Delta)> joinDelta,
                function<Value(Value, Delta, int, int)> accumulate,
                Value defaultValue = 0, Delta defaultDelta = 0) :
            size(size), joinValue(joinValue), joinDelta(joinDelta), accumulate(accumulate),
            defaultValue(defaultValue), defaultDelta(defaultDelta) {
        int vertexSize = size * 4;
        value = arr<Value>(vertexSize);
        delta = arr<Delta>(vertexSize, defaultDelta);
        if (size > 0) {
            init(0, 0, size);
        }
    }

    void update(int from, int to, Delta delta) {
        update(0, 0, size, max(0, from), to, delta);
    }

    Value query(int from, int to) {
        return query(0, 0, size, max(0, from), to);
    }
};

template<typename Value, Value defaultValue = 0>
class ReadOnlySegmentTree {
private:
    const int size;
    function<Value(Value, Value)> joinValue;
    arr<Value> value;

    void init(int root, int left, int right, const arr<Value> &array) {
        if (left + 1 == right) {
            value[root] = array[left];
        } else {
            int mid = (left + right) >> 1;
            init(2 * root + 1, left, mid, array);
            init(2 * root + 2, mid, right, array);
            value[root] = joinValue(value[2 * root + 1], value[2 * root + 2]);
        }
    }

    Value query(int root, int left, int right, int from, int to) const {
        if (left >= from && right <= to) {
            return value[root];
        }
        if (right <= from || left >= to) {
            return defaultValue;
        }
        int mid = (left + right) >> 1;
        Value lValue = query(2 * root + 1, left, mid, from, to);
        Value rValue = query(2 * root + 2, mid, right, from, to);
        return joinValue(lValue, rValue);
    }

public:
    ReadOnlySegmentTree(const arr<Value> &array, function<Value(Value, Value)> joinValue) :
            size(array.size()), joinValue(joinValue) {
        int vertexSize = size * 4;
        value = arr<Value>(vertexSize);
        if (size > 0) {
            init(0, 0, size, array);
        }
    }

    Value query(int from, int to) const {
        return query(0, 0, size, max(0, from), to);
    }
};


template<class Edge>
class LCA {
private:
    arri order;
    arri position;
    ReadOnlySegmentTree<int, -1> *lcaTree;

public:
    arri level;
    arri parent;

    LCA(Graph<Edge> &graph, int root = 0) {
        int vertexCount = graph.vertexCount;
        order = arri(2 * vertexCount - 1);
        position = arri(vertexCount, -1);
        level = arri(vertexCount);
        level[root] = 0;
        arri index(vertexCount, 0);
        parent = arri(vertexCount);
        arri &last = parent;
        arri stack(vertexCount);
        stack[0] = root;
        int size = 1;
        int j = 0;
        last[root] = -1;
        while (size > 0) {
            int vertex = stack[--size];
            if (position[vertex] == -1) {
                position[vertex] = j;
            }
            order[j++] = vertex;
            if (last[vertex] != -1) {
                level[vertex] = level[last[vertex]] + 1;
            }
            while (index[vertex] < graph[vertex].size() && last[vertex] == graph[vertex][index[vertex]]->to) {
                index[vertex]++;
            }
            if (index[vertex] < graph[vertex].size()) {
                stack[size++] = vertex;
                int to = graph[vertex][index[vertex]]->to;
                stack[size++] = graph[vertex][index[vertex]]->to;
                last[to] = vertex;
                index[vertex]++;
            }
        }
        lcaTree = new ReadOnlySegmentTree<int, -1>(order, [this](int left, int right) -> int {
            if (left == -1) {
                return right;
            }
            if (right == -1) {
                return left;
            }
            if (level[left] < level[right]) {
                return left;
            }
            return right;
        });
    }

    int lca(int first, int second) const {
        return lcaTree->query(min(position[first], position[second]), max(position[first], position[second]) + 1);
    }

    int pathLength(int first, int second) const {
        return level[first] + level[second] - 2 * level[lca(first, second)];
    }
};


template<class Edge>
class DFSOrder {
public:
    arri position;
    arri end;

    DFSOrder(Graph<Edge> &graph, int root = 0) {
        int count = graph.vertexCount;
        position = arri(count);
        end = arri(count);
        arri edge(count, 0);
        arri stack(count);
        arri last(count);
        stack[0] = root;
        last[root] = -1;
        int size = 1;
        position[root] = 0;
        int index = 0;
        while (size > 0) {
            int current = stack[size - 1];
            int &cEdge = edge[current];
            if (cEdge == graph[current].size()) {
                end[current] = index;
                size--;
            } else {
                int next = graph[current][cEdge]->to;
                if (next == last[current]) {
                    cEdge++;
                    continue;
                }
                cEdge++;
                position[next] = ++index;
                last[next] = current;
                stack[size++] = next;
            }
        }
    }
};


//#pragma comment(linker, "/STACK:200000000")

class c {
public:
    void solve(istream &inp, ostream &outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        int q = in.readInt();
        int k = in.readInt();
        auto x = in.readArray<ll>(n);
        arri u, v;
        in.readArrays(n - 1, u, v);
        decreaseByOne(u, v);

        Matrix<modint> m(3, 3);
        m[0][1] = 1;
        m[1][2] = 1;
        m[2][0] = k - 2;
        m[2][2] = k;
        arr<Matrix<modint>> pow(70);
        pow[0] = m;
        for (int i : range(1, 70)) {
            pow[i] = Matrix<modint>(3, 3);
            multiply(pow[i], pow[i - 1], pow[i - 1]);
        }
        Matrix<modint> res1(3, 3);
        Matrix<modint> res2(3, 3);
        auto f = [&](ll exp) -> modint {
            exp--;
            int at = 0;
            res1.makeOne();
            bool inv = false;
            while (exp != 0) {
                if ((exp & 1) == 1) {
                    if (inv) {
                        multiply(res1, res2, pow[at]);
                    } else {
                        multiply(res2, res1, pow[at]);
                    }
                    inv = !inv;
                }
                at++;
                exp >>= 1;
            }
            auto& res = inv ? res2 : res1;
            return res[0][0] + 2 * res[0][1] + 5 * res[0][2];
        };
        arr<modint> val(n);
        for (int i : range(n)) {
            val[i] = f(x[i]);
        }
        Graph<BiEdge> graph(n);
        for (int i : range(n - 1)) {
            graph.addEdge(u[i], v[i]);
        }
        LCA<BiEdge> lca(graph);
        DFSOrder<BiEdge> order(graph);
        arr<modint> tree(4 * n, modint(0));
        function<void(int, int, int, int, int, modint)> updateImpl = [&](int root, int left, int right, int from, int to, modint delta) {
            if (left >= to || right <= from) {
                return;
            }
            if (left >= from && right <= to) {
                tree[root] += delta;
                return;
            }
            int mid = (left + right) / 2;
            updateImpl(2 * root + 1, left, mid, from, to, delta);
            updateImpl(2 * root + 2, mid, right, from, to, delta);
        };
        auto update = [&](int from, int to, modint delta) {
            updateImpl(0, 0, n, from, to, delta);
        };
        function<modint(int, int, int, int)> queryImpl = [&](int root, int left, int right, int at) -> modint {
            modint res = tree[root];
            if (left + 1 != right) {
                int mid = (left + right) / 2;
                if (at < mid) {
                    res += queryImpl(2 * root + 1, left, mid, at);
                } else {
                    res += queryImpl(2 * root + 2, mid, right, at);
                }
            }
            return res;
        };
        auto query = [&](int at) -> modint {
            return queryImpl(0, 0, n, at);
        };
        for (int i : range(n)) {
            update(order.position[i], order.end[i] + 1, val[i]);
        }
        for (int i : range(q)) {
            int type = in.readInt();
            if (type == 1) {
                int u = in.readInt() - 1;
                int v = in.readInt() - 1;
                int lc = lca.lca(u, v);
                modint answer = query(order.position[u]) +
                                query(order.position[v]) -
                                2 * query(order.position[lc]) + val[lc];
                out.printLine(answer);
            } else {
                int u = in.readInt() - 1;
                ll nx = in.readLong();
                modint nv = f(nx);
                modint delta = nv - val[u];
                val[u] = nv;
                update(order.position[u], order.end[u] + 1, delta);
            }
        }
    }
};


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    c solver;
    std::istream &in(std::cin);
    std::ostream &out(std::cout);
    solver.solve(in, out);
    return 0;
}
