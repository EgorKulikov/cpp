#pragma once

#include "../general.h"
#include "../numbers/doubles.h"
#include "../collections/arr.h"
#include "../collections/mdarr.h"

inline bool isWhitespace(int c) {
    return isspace(c) || c == EOF;
}

class Input {
private:
    istream &in;
    bool exhausted = false;

    inline int get() {
        if (exhausted) {
            throw "Input exhausted";
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
                throw "Number format error";
            }
            res *= 10;
            res += c - '0';
            c = get();
        } while (!isWhitespace(c));
        return res * sgn;
    }

    void initArrays(int n) {}

    template <typename T, class...Vs>
    void initArrays(int n, arr<T>& array, Vs&...vs) {
        array = arr<T>(n);
        initArrays(n, vs...);
    }

    void readImpl(int i) {}

    template <typename T, class...Vs>
    void readImpl(int i, arr<T>& arr, Vs&...vs) {
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
            throw "Input exhausted";
        }
        vector<char> res;
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



    template <class...Vs>
    void readArrays(int n, Vs&...vs) {
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

    template<typename T>
    arr2d<T> readTable(int rows, int cols) {
        arr2d<T> result(rows, cols);
        result.reserve(rows);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result(i, j) = readType<T>();
            }
        }
        return result;
    }

    string readLine() {
        skipWhitespace();
        int c = get();
        if (c == EOF) {
            throw "Input exhausted";
        }
        int length = 0;
        vector<char> res;
        do {
            res.push_back(c);
            if (!isWhitespace(c)) {
                length = res.size();
            }
            c = get();
        } while (c != '\n' && c != '\r' && c != EOF);
        return string(res.begin(), res.begin() + length);
    }

    double readDouble() {
        skipWhitespace();
        int c = get();
        int sgn = 1;
        if (c == '-') {
            sgn = -1;
            c = get();
        }
        double res = 0;
        do {
            if (tolower(c) == 'e') {
                return sgn * res * dPower(10, readInt());
            }
            if (!isdigit(c)) {
                throw "Number format error";
            }
            res *= 10;
            res += c - '0';
            c = get();
        } while (!isWhitespace(c) && c != '.');
        if (c == '.') {
            double add = 0;
            int length = 0;
            c = get();
            do {
                if (tolower(c) == 'e') {
                    return sgn * (res + add * dPower(10, -length)) * dPower(10, readInt());
                }
                if (!isdigit(c)) {
                    throw "Number format error";
                }
                add *= 10;
                add += c - '0';
                length++;
                c = get();
            } while (!isWhitespace(c));
            res += add * dPower(10, -length);
        }
        return res * sgn;
    }

    char readChar() {
        skipWhitespace();
        int c = get();
        if (c == EOF) {
            throw "Input exhausted";
        }
        return c;
    }

    bool isExhausted() { return exhausted; }
};

template<>
double Input::readType() {
    return readDouble();
}

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
