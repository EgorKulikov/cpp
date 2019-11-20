#ifndef CPP_OUTPUT_H
#define CPP_OUTPUT_H

#include "../general.h"

class Output {
private:
    ostream& out;
    template<typename T> void printSingle(const T& value);
    template<typename T> void printSingle(const vector<T>& value);
    template<typename T, typename U> void printSingle(const pair<T, U>& value);

public:
    Output(ostream& out);
    void print();
    template<typename T, typename...Targs>void print(const T& first, const Targs... args);
    template<typename...Targs>void printLine(const Targs... args);
};

Output::Output(ostream &out) : out(out) {
    out << setprecision(12);
}

void Output::print() {
}

template<typename T, typename... Targs>
void Output::print(const T& first, const Targs... args) {
    printSingle(first);
    if (sizeof...(args) != 0) {
        out << ' ';
        print(args...);
    }
}

template<typename T>
void Output::printSingle(const T& value) {
    out << value;
}

template<typename... Targs>
void Output::printLine(const Targs... args) {
    print(args...);
    out << '\n';
}

template<typename T>
void Output::printSingle(const vector<T>& array) {
    unsigned int size = array.size();
    for (int i = 0; i < size; ++i) {
        out << array[i];
        if (i + 1 != size) {
            out << ' ';
        }
    }
}

template<typename T, typename U>
void Output::printSingle(const pair<T, U>& value) {
    out << value.first << ' ' << value.second;
}

#endif
