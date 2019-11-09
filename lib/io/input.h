#ifndef JHELPER_EXAMPLE_PROJECT_INPUT_H
#define JHELPER_EXAMPLE_PROJECT_INPUT_H

#include "../general.h"

class Input {
public:
    enum ErrorType {
        OK,
        END_OF_FILE,
        UNEXPECTED_SYMBOL,
        INVALID_CALL
    };

private:
    istream& in;
    bool exhausted = false;
    ErrorType error = OK;
    int get();
    template<typename T> T readInteger();
    int skipWhitespace();

public:
    Input(istream& in);
    int readInt();
    ll readLong();
    string readString();
    vector<int> readIntArray(int size);
    template<typename T> T readType();
    template<typename T, typename U> pair<T, U> readType();
    template<typename T> vector<T> readArray(int size);
    template<typename T1, typename T2> tuple<vector<T1>, vector<T2> > readArrays(int size);
    template<typename T1, typename T2, typename T3> tuple<vector<T1>, vector<T2>, vector<T3> > readArrays(int size);
    template<typename T1, typename T2, typename T3, typename T4>
        tuple<vector<T1>, vector<T2>, vector<T3>, vector<T4> > readArrays(int size);
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
        tuple<vector<T1>, vector<T2>, vector<T3>, vector<T4>, vector<T5> > readArrays(int size);
    template<typename T> vector<vector<T> > readTable(int rows, int cols);

    string readLine();
    double readDouble();
};

inline bool isWhitespace(int c) {
    return isspace(c) || c == EOF;
}

int Input::skipWhitespace() {
    int c;
    do {
        c = get();
        if (exhausted) {
            error = END_OF_FILE;
            return c;
        }
    } while (isWhitespace(c));
    return c;
}

Input::Input(std::istream &in) : in(in) {
}

inline int Input::get() {
    int result = in.get();
    if (result == EOF) {
        exhausted = true;
    }
    return result;
}

template<typename T>
T Input::readType() {
    error = INVALID_CALL;
    return nullptr;
}

template<>
double Input::readType() {
    error = OK;
    int c = skipWhitespace();
    if (error != OK) {
        return 0;
    }
    int sgn = 1;
    if (c == '-') {
        sgn = -1;
        c = get();
    }
    double res = 0;
    do {
        if (!isdigit(c)) {
            error = UNEXPECTED_SYMBOL;
            return 0;
        }
        res *= 10;
        res += c - '0';
        c = get();
    } while (!isWhitespace(c) && c != '.');
    if (c == '.') {
        vi digits;
        c = get();
        do {
            if (!isdigit(c)) {
                error = UNEXPECTED_SYMBOL;
                return 0;
            }
            digits.push_back(c - '0');
            c = get();
        } while (!isWhitespace(c));
        double add = 0;
        for (int i = int(digits.size()) - 1; i >= 0; i--) {
            add += digits[i];
            add /= 10;
        }
        res += add;
    }
    return res;
}

template<typename T>
T Input::readInteger() {
    error = OK;
    int c = skipWhitespace();
    if (error != OK) {
        return 0;
    }
    int sgn = 1;
    if (c == '-') {
        sgn = -1;
        c = get();
    }
    T res = 0;
    do {
        if (!isdigit(c)) {
            error = UNEXPECTED_SYMBOL;
            return 0;
        }
        res *= 10;
        res += c - '0';
        c = get();
    } while (!isWhitespace(c));
    return res * sgn;
}

template<>
int Input::readType() {
    return readInteger<int>();
}

template<>
ll Input::readType() {
    return readInteger<ll>();
}

template<>
char Input::readType() {
    error = OK;
    int c = skipWhitespace();
    if (error != OK) {
        return 0;
    }
    return c;
}

template<>
string Input::readType() {
    error = OK;
    int c = skipWhitespace();
    if (error != OK) {
        return "";
    }
    vector<char> res;
    do {
        if (error != OK) {
            return "";
        }
        res.push_back(c);
    } while (!isWhitespace(c = get()));
    return string(res.begin(), res.end());
}

inline int Input::readInt() {
    return readType<int>();
}

inline ll Input::readLong() {
    return readType<ll>();
}

template<typename T>
vector<T> Input::readArray(int size) {
    vector<T> res;
    res.reserve(size);
    for (int i = 0; i < size; i++) {
        res.push_back(readType<T>());
        if (error != OK) {
            res.clear();
            return res;
        }
    }
    return res;
}

vector<int> Input::readIntArray(int size) {
    return readArray<int>(size);
}

template<typename T1, typename T2>
tuple<vector<T1>, vector<T2> > Input::readArrays(int size) {
    vector<T1> v1;
    vector<T2> v2;
    v1.reserve(size);
    v2.reserve(size);
    for (int i = 0; i < size; ++i) {
        v1.push_back(readType<T1>());
        v2.push_back(readType<T2>());
    }
    return make_tuple(v1, v2);
}

string Input::readString() {
    return readType<string>();
}

template<typename T>
vector<vector<T>> Input::readTable(int rows, int cols) {
    vector<vector<T> > result;
    result.reserve(rows);
    for (int i = 0; i < rows; ++i) {
        result.push_back(readArray<T>(cols));
    }
    return result;
}

string Input::readLine() {
    error = OK;
    int c = skipWhitespace();
    if (error != OK) {
        return "";
    }
    int length = 0;
    vector<char> res;
    do {
        if (error != OK) {
            return "";
        }
        res.push_back(c);
        if (!isWhitespace(c)) {
            length = res.size();
        }
        c = get();
    } while (c != '\n' && c != '\r' && c != EOF);
    return string(res.begin(), res.begin() + length);
}

double Input::readDouble() {
    return readType<double>();
}

template<typename T1, typename T2, typename T3>
tuple<vector<T1>, vector<T2>, vector<T3> > Input::readArrays(int size) {
    vector<T1> v1;
    vector<T2> v2;
    vector<T3> v3;
    v1.reserve(size);
    v2.reserve(size);
    v3.reserve(size);
    for (int i = 0; i < size; ++i) {
        v1.push_back(readType<T1>());
        v2.push_back(readType<T2>());
        v3.push_back(readType<T3>());
    }
    return make_tuple(v1, v2, v3);
}

template<typename T1, typename T2, typename T3, typename T4>
tuple<vector<T1>, vector<T2>, vector<T3>, vector<T4> > Input::readArrays(int size) {
    vector<T1> v1;
    vector<T2> v2;
    vector<T3> v3;
    vector<T4> v4;
    v1.reserve(size);
    v2.reserve(size);
    v3.reserve(size);
    v4.reserve(size);
    for (int i = 0; i < size; ++i) {
        v1.push_back(readType<T1>());
        v2.push_back(readType<T2>());
        v3.push_back(readType<T3>());
        v4.push_back(readType<T4>());
    }
    return make_tuple(v1, v2, v3, v4);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5>
tuple<vector<T1>, vector<T2>, vector<T3>, vector<T4>, vector<T5> > Input::readArrays(int size) {
    vector<T1> v1;
    vector<T2> v2;
    vector<T3> v3;
    vector<T4> v4;
    vector<T5> v5;
    v1.reserve(size);
    v2.reserve(size);
    v3.reserve(size);
    v4.reserve(size);
    v5.reserve(size);
    for (int i = 0; i < size; ++i) {
        v1.push_back(readType<T1>());
        v2.push_back(readType<T2>());
        v3.push_back(readType<T3>());
        v4.push_back(readType<T4>());
        v5.push_back(readType<T5>());
    }
    return make_tuple(v1, v2, v3, v4, v5);
}

#endif //JHELPER_EXAMPLE_PROJECT_INPUT_H
