#pragma once

#include "modulo.h"
#include "numbers.h"

namespace prime_fft {
    bool init = false;
    ModuloInt root;
    ModuloInt reverseRoot;
    int rootPower;
    vector<ModuloInt> aa;
    vector<ModuloInt> bb;
}

void initPrimeFFT() {
    if (prime_fft::init) {
        return;
    }
    prime_fft::init = true;
    prime_fft::rootPower = 1;
    int pw = 0;
    while ((mod - 1) % (2 * prime_fft::rootPower) == 0) {
        prime_fft::rootPower *= 2;
        pw++;
    }
    for (int i = 2; ; i++) {
        mod--;
        int exp = power(ModuloInt(2), pw - 1).n;
        int next = (exp * 2) % mod;
        mod++;
        if (power(ModuloInt(i), exp).n != 1 && power(ModuloInt(i), next).n == 1) {
            prime_fft::root = i;
            prime_fft::reverseRoot = power(prime_fft::root, mod - 2);
            break;
        }
    }
}

namespace prime_fft {
    void primeFFT(vector<ModuloInt>& array, bool invert, int size) {
        for (int i = 1, j = 0; i < size; ++i) {
            int bit = size >> 1;
            for (; j >= bit; bit >>= 1) {
                j -= bit;
            }
            j += bit;
            if (i < j) {
                swap(array[i], array[j]);
            }
        }

        for (int len = 2; len <= size; len <<= 1) {
            ModuloInt wlen = invert ? reverseRoot : root;
            for (int i = len; i < rootPower; i <<= 1) {
                wlen *= wlen;
            }
            int half = len >> 1;
            for (int i = 0; i < size; i += len) {
                ModuloInt w = 1;
                for (int j = 0; j < half; ++j) {
                    ModuloInt u = array[i + j], v = array[i + j + half] * w;
                    array[i + j] = u + v;
                    array[i + j + half] = u - v;
                    w *= wlen;
                }
            }
        }
        if (invert) {
            ModuloInt reverseSize = power(ModuloInt(size), mod - 2);
            for (int i = 0; i < size; ++i) {
                array[i] *= reverseSize;
            }
        }
    }

}

vector<ModuloInt> multiply(const vector<ModuloInt>& first, const vector<ModuloInt>& second) {
    int resLen = first.size() + second.size() - 1;
    if (resLen <= 100) {
        vector<ModuloInt> result(resLen);
        for (int i = 0; i < first.size(); i++) {
            for (int j = 0; j < second.size(); j++) {
                result[i + j] += first[i] * second[j];
            }
        }
        return result;
    }
    int resultSize = 1;
    while (resultSize < resLen) {
        resultSize *= 2;
    }
    vector<ModuloInt>& aa = prime_fft::aa;
    vector<ModuloInt>& bb = prime_fft::bb;
    if (aa.size() < resultSize) {
        aa.resize(resultSize);
        bb.resize(resultSize);
    }
    fill(aa.begin() + first.size(), aa.begin() + resultSize, ModuloInt(0));
    fill(bb.begin() + second.size(), bb.begin() + resultSize, ModuloInt(0));
    for (int i = 0; i < first.size(); i++) {
        aa[i] = first[i];
    }
    for (int i = 0; i < second.size(); i++) {
        bb[i] = second[i];
    }
    prime_fft::primeFFT(aa, false, resultSize);
//    if (first == second) {
//        copy(all(aa), bb.begin());
//    } else {
    prime_fft::primeFFT(bb, false, resultSize);
//    }
    for (int i = 0; i < resultSize; i++) {
        aa[i] *= bb[i];
    }
    prime_fft::primeFFT(aa, true, resultSize);
    vector<ModuloInt> result(resLen);
    for (int i = 0; i < result.size(); i++) {
        result[i] = aa[i];
    }
    return result;
}

