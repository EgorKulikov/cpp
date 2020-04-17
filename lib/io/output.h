#pragma once

#include <iostream>
#include <iomanip>
#include "../general.h"
#include "../collections/arr.h"
#include "../collections/mdarr.h"

class Output {
private:
    ostream& out = cout;

    template<typename T> void printSingle(const T& value) {
        out << value;
    }

    template<typename T> void printSingle(const vector<T>& array) {
        size_t n = array.size();
        for (int i = 0; i < n; ++i) {
            out << array[i];
            if (i + 1 != n) {
                out << ' ';
            }
        }
    }
    template<typename T> void printSingle(const arr<T>& array) {
        size_t n = array.size();
        for (int i = 0; i < n; ++i) {
            out << array[i];
            if (i + 1 != n) {
                out << ' ';
            }
        }
    }
    template<typename T> void printSingle(const arr2d<T>& array) {
        size_t n = array.dim1();
        size_t m = array.dim2();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                out << array(i, j);
                if (j + 1 != m) {
                    out << ' ';
                }
            }
            if (i + 1 != n) {
                out << '\n';
            }
        }
    }
    template<typename T, typename U> void printSingle(const pair<T, U>& value) {
        out << value.first << ' ' << value.second;
    }

public:
    Output() {//ostream& out) : out(out) {
        out << fixed << setprecision(20);
    }

    void print() {}

    template<typename T, typename...Targs>
    void print(const T& first, const Targs... args) {
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

    void setPrecision(int digs) {
        out << fixed << setprecision(digs);
    }
};

Output out;
