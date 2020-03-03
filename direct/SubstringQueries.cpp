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
inline void unique(vec<T>& v) {
    v.resize(unique(all(v)) - v.begin());
}

arri createOrder(int n) {
    arri order(n);
    for (int i = 0; i < n; i++) {
        order[i] = i;
    }
    return order;
}

arri inverse(const arri& p) {
    arri res(p.size());
    for (int i : range(p.size())) {
        res[p[i]] = i;
    }
    return res;
}

template <typename T, typename Iterator>
inline void addAll(vec<T>& v, Iterator begin, Iterator end) {
    v.insert(v.end(), begin, end);
}

template <class Collection, typename Iterator>
inline void addAll(Collection& v, Iterator begin, Iterator end) {
    v.insert(begin, end);
}

template <typename Iterator>
arri getQty(Iterator begin, Iterator end, int length) {
    arri res(length, 0);
    for (Iterator it = begin; it != end; it++) {
        res[*it]++;
    }
    return res;
}

template <typename Iterator>
arri getQty(Iterator begin, Iterator end) {
    return getQty(begin, end, *max_element(begin, end) + 1);
}

template <class Collection>
void collect(Collection&) {}

template <class Collection, class Other, class ...Vs>
void collect(Collection& all, Other& a, Vs&...vs) {
    addAll(all, all(a));
    collect(all, vs...);
}

void replace(const vi&) {}

template <class ...Vs>
void replace(const vi& all, vi& a, Vs&...vs) {
    for (int& i : a) {
        i = lower_bound(all(all), i) - all.begin();
    }
    replace(all, vs...);
}

template <class ...Vs>
void replace(const vi& all, arri& a, Vs&...vs) {
    for (int& i : a) {
        i = lower_bound(all(all), i) - all.begin();
    }
    replace(all, vs...);
}

template <class ...Vs>
vi compress(Vs&...vs) {
    vi vals;
    collect(vals, vs...);
    sort(all(vals));
    unique(vals);
    replace(vals, vs...);
    return vals;
}








const int MOD7 = 1000000007;
const int MOD9 = 1000000009;
const int MODF = 998244353;

int mod = MOD7;

template <typename T>
T gcd(T a, T b, T& x, T& y) {
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
    modint& operator +=(const modint& other) {
        n += other.n;
        if (n >= mod) {
            n -= mod;
        }
        return *this;
    }
    modint& operator -=(const modint& other) {
        n -= other.n;
        if (n < 0) {
            n += mod;
        }
        return *this;
    }
    modint& operator *=(const modint& other) {
        n = ll(n) * other.n % mod;
        return *this;
    }
    modint& operator /=(const modint& other) {
#ifdef LOCAL
        if (other.n == 0) {
            throw "Division by zero";
        }
#endif
        return *this *= other.inverse();
    }
    modint operator -() {
        if (n == 0) {
            return 0;
        }
        return modint(mod - n);
    }
    modint inverse() const {
        ll x, y;
        ll g = gcd(ll(n), ll(mod), x, y);
#ifdef LOCAL
        if (g != 1) {
            throw "not inversable";
        }
#endif
        return x;
    }
    int log(modint alpha);
};

modint operator +(const modint& a, const modint& b) {
    return modint(a) += b;
}

modint operator -(const modint& a, const modint& b) {
    return modint(a) -= b;
}

modint operator *(const modint& a, const modint& b) {
    return modint(a) *= b;
}

modint operator /(const modint& a, const modint& b) {
    return modint(a) /= b;
}

ostream& operator <<(ostream& out, const modint& val) {
    return out << val.n;
}

bool operator==(const modint& a, const modint& b) {
    return a.n == b.n;
}

bool operator!=(const modint& a, const modint& b) {
    return a.n != b.n;
}

namespace std {
    template <>
    struct hash<modint> {
        size_t operator ()(const modint& n) const {
            return n.n;
        }
    };
}

int modint::log(modint alpha) {
    unordered_map<modint, int> base;
    int exp = 0;
    modint pow = 1;
    modint inv = *this;
    modint alInv = alpha.inverse();
    while (exp * exp < mod) {
        if (inv == 1) {
            return exp;
        }
        base[inv] = exp++;
        pow *= alpha;
        inv *= alInv;
    }
    modint step = pow;
    for (int i = 1; ; i++) {
        if (base.count(pow)) {
            return exp * i + base[pow];
        }
        pow *= step;
    }
}






vec<bool> primalityTable(int n) {
    vec<bool> res(n, true);
    if (n > 0) {
        res[0] = false;
    }
    if (n > 1) {
        res[1] = false;
    }
    for (int i = 2; i * i < n; i++) {
        if (res[i]) {
            for (int j = i * i; j < n; j += i) {
                res[j] = false;
            }
        }
    }
    return res;
}

arri divisorTable(int n) {
    arri res(n, 0);
    if (n > 1) {
        res[1] = 1;
    }
    for (int i = 2; i < n; i++) {
        if (res[i] == 0) {
            res[i] = i;
            if (ll(i) * i < n) {
                for (int j = i * i; j < n; j += i) {
                    res[j] = i;
                }
            }
        }
    }
    return res;
}

vi primes(int n) {
    auto isPrime = primalityTable(n);
    vi res;
    for (int i = 0; i < n; ++i) {
        if (isPrime[i]) {
            res.push_back(i);
        }
    }
    return res;
}

bool isPrime(long n) {
    if (n < 2) {
        return false;
    }
    for (long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

ll nextPrime(ll n) {
    if (n <= 2) {
        return 2;
    }
    n += 1 - (n & 1);
    while (!isPrime(n)) {
        n += 2;
    }
    return n;
}


namespace string_hash {
    bool initDone = false;
    int firstMod;
    int secondMod;
    modint multiplier;
    modint firstRevMultiplier;
    modint secondRevMultiplier;

    void stringHashInit() {
        int wasMod = mod;
        random_device rd;
        mt19937_64 gen(rd());
        firstMod = nextPrime(500000000 + gen() % 500000000);
        secondMod = nextPrime(500000000 + gen() % 500000000);
        mod = firstMod;
        multiplier = 257 + gen() % (500000000 - 257);
        firstRevMultiplier = multiplier.inverse();
        mod = secondMod;
        secondRevMultiplier = multiplier.inverse();
        mod = wasMod;
        initDone = true;
    }


    vec<modint> firstRevPow;
    vec<modint> secondRevPow;
    vec<modint> firstPower;
    vec<modint> secondPower;

    void ensureCapacity(int n) {
        int wasMod = mod;
        mod = firstMod;
        while (firstRevPow.size() < n) {
            if (firstRevPow.empty()) {
                firstRevPow.push_back(1);
            } else {
                firstRevPow.push_back(firstRevPow.back() * firstRevMultiplier);
            }
        }
        while (firstPower.size() < n) {
            if (firstPower.empty()) {
                firstPower.push_back(1);
            } else {
                firstPower.push_back(firstPower.back() * multiplier);
            }
        }
        mod = secondMod;
        while (secondRevPow.size() < n) {
            if (secondRevPow.empty()) {
                secondRevPow.push_back(1);
            } else {
                secondRevPow.push_back(secondRevPow.back() * secondRevMultiplier);
            }
        }
        while (secondPower.size() < n) {
            if (secondPower.empty()) {
                secondPower.push_back(1);
            } else {
                secondPower.push_back(firstPower.back() * multiplier);
            }
        }
        mod = wasMod;
    }
}

class StringHash {
    arr<modint> firstHash;
    arr<modint> secondHash;

    template <typename Collection>
    void doPower(arr<modint>& hash, int cMod, const Collection& str) {
        using namespace string_hash;
        int wasMod = mod;
        mod = cMod;
        hash = arr<modint>(str.size() + 1);
        hash[0] = 0;
        modint power = 1;
        for (int i : range(str.size())) {
            hash[i + 1] = hash[i] + str[i] * power;
            power *= multiplier;
        }
        mod = wasMod;
    }

public:
    template <typename Collection>
    explicit StringHash(const Collection& str) {
        using namespace string_hash;
        if (!initDone) {
            stringHashInit();
        }
        ensureCapacity(str.size() + 1);
        doPower(firstHash, firstMod, str);
        doPower(secondHash, secondMod, str);
    }

    ll hash(int from, int to) const {
#ifdef LOCAL
        if (from < 0 || to < from || to > length()) {
            throw "Out of bounds";
        }
#endif
        using namespace string_hash;
        int wasMod = mod;
        mod = firstMod;
        ll first = ((firstHash[to] - firstHash[from]) * firstRevPow[from]).n;
        mod = secondMod;
        ll second = ((secondHash[to] - secondHash[from]) * secondRevPow[from]).n;
        mod = wasMod;
        return (first << 32) + second;
    }

    int length() const {
        return firstHash.size() - 1;
    }

    ll hash(int from) const {
        return hash(from, length());
    }
};

template <class Hash>
struct SubstringHash {
    const Hash& base;
    const int from;
    const int to;

    SubstringHash(const Hash& base, int from, int to) : base(base), from(from), to(to) {}

    SubstringHash(const Hash& base, int from) : SubstringHash(base, from, base.length()) {}

    ll hash(int from, int to) const {
#ifdef LOCAL
        if (from < 0 || to < from || to > length()) {
            throw "Out of bounds";
        }
#endif
        return base.hash(from + this->from, to + this->to);
    }

    int length() const {
        return to - from;
    }

    ll hash(int from) const {
        return hash(from, length());
    }
};

template <class Hash>
SubstringHash<Hash> substringHash(const Hash& base, int from, int to) {
    return SubstringHash<Hash>(base, from, to);
}

template <class Hash>
SubstringHash<Hash> substringHash(const Hash& base, int from) {
    return SubstringHash<Hash>(base, from);
}

template <class Hash1, class Hash2>
struct CompositeHash {
    const Hash1& base1;
    const Hash2& base2;

    CompositeHash(const Hash1& base1, const Hash2& base2) : base1(base1), base2(base2) {
        using namespace string_hash;
        ensureCapacity(base1.length() + 1);
    }

    ll hash(int from, int to) {
#ifdef LOCAL
        if (from < 0 || to < from || to > length()) {
            throw "Out of bounds";
        }
#endif
        using namespace string_hash;
        if (to <= base1.length()) {
            return base1.hash(from, to);
        }
        if (from >= base1.length()) {
            return base2.hash(from - base1.length(), to - base1.length());
        }
        ll h1 = base1.hash(from);
        ll h2 = base2.hash(0, to - base1.length());
        int wasMod = mod;
        mod = firstMod;
        ll first = (modint(h1 >> 32) * firstPower[base1.length() - from] + modint(h2 >> 32)).n;
        mod = secondMod;
        ll second = (modint(h1 & numeric_limits<unsigned>::max()) * firstPower[base1.length() - from] + modint(h2 & numeric_limits<unsigned>::max())).n;
        mod = wasMod;
        return (first << 32) + second;
    }

    int length() const {
        return base1.length() + base2.length();
    }

    ll hash(int from) const {
        return hash(from, length());
    }
};

template <class Hash1, class Hash2>
CompositeHash<Hash1, Hash2> compositeHash(const Hash1& base1, const Hash2& base2) {
    return CompositeHash<Hash1, Hash2>(base1, base2);
}


using namespace std;

class SubstringQueries {
public:
    long long solve(string s, ll k) {
        for (int i : range(1, s.size())) {
            if (s.size() % i) {
                continue;
            }
            bool good = true;
            for (int j : range(i, s.size())) {
                if (s[j] != s[j - i]) {
                    good = false;
                    break;
                }
            }
            if (good) {
                s = s.substr(0, i);
                k *= s.size() / i;
                break;
            }
        }
        int n = s.size();
        vi pos;
        for (int i : range(n)) {
            pos.push_back(i);
        }
        ll answer = 0;
        for (int i : range(n)) {
            vi next;
            int best = 'z' + 1;
            for (int j : pos) {
                if (k == 1 && j + i >= n) {
                    continue;
                }
                if (s[(j + i) % n] < best) {
                    best = s[(j + i) % n];
                    next.clear();
                }
                if (s[(j + i) % n] == best) {
                    next.push_back(j);
                }
            }
            answer += next[0];
            next.swap(pos);
        }
        if (k == 1) {
            return answer;
        }
        answer += ll(pos[0]) * (k - 2) * n;
        StringHash hash(s + s);
        auto order = createOrder(n);
        sort(all(order), [&](int a, int b) -> bool {
            int left = 0;
            int right = s.size();
            while (left < right) {
                int mid = (left + right + 1) / 2;
                if (hash.hash(a, a + mid) == hash.hash(b, b + mid)) {
                    left = mid;
                } else {
                    right = mid - 1;
                }
            }
            return s[(a + left) % n] < s[(b + left) % n];
        });
        int at = 0;
        for (int i : range(n)) {
            while (order[at] + i >= n) {
                at++;
            }
            answer += order[at];
        }
        return answer;
    }


// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "aaaaaaaaa"; int Arg1 = 1; long long Arg2 = 0LL; verify_case(0, Arg2, solve(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "zaba"; int Arg1 = 2; long long Arg2 = 7LL; verify_case(1, Arg2, solve(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "acaa"; int Arg1 = 2; long long Arg2 = 10LL; verify_case(2, Arg2, solve(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "zberba"; int Arg1 = 1; long long Arg2 = 65LL; verify_case(3, Arg2, solve(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
    SubstringQueries ___test;
    ___test.run_test(3);
}
// END CUT HERE
