#pragma once

#include "modulo.h"
#include "numbers.h"

namespace prime_fft {
    bool init = false;
    modint root;
    modint reverseRoot;
    int rootPower;
    vector<modint> aa;
    vector<modint> bb;
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
        int exp = power(modint(2), pw - 1).n;
        int next = (exp * 2) % mod;
        mod++;
        if (power(modint(i), exp).n != 1 && power(modint(i), next).n == 1) {
            prime_fft::root = i;
            prime_fft::reverseRoot = prime_fft::root.inverse();
            break;
        }
    }
}

namespace prime_fft {
    void primeFFT(vector<modint>& array, bool invert, int n) {
        for (int i = 1, j = 0; i < n; ++i) {
            int bit = n >> 1;
            for (; j >= bit; bit >>= 1) {
                j -= bit;
            }
            j += bit;
            if (i < j) {
                swap(array[i], array[j]);
            }
        }

        for (int len = 2; len <= n; len <<= 1) {
            modint wlen = invert ? reverseRoot : root;
            for (int i = len; i < rootPower; i <<= 1) {
                wlen *= wlen;
            }
            int half = len >> 1;
            for (int i = 0; i < n; i += len) {
                modint w = 1;
                for (int j = 0; j < half; ++j) {
                    modint u = array[i + j], v = array[i + j + half] * w;
                    array[i + j] = u + v;
                    array[i + j + half] = u - v;
                    w *= wlen;
                }
            }
        }
        if (invert) {
            modint reverseSize = modint(n).inverse();
            for (int i = 0; i < n; ++i) {
                array[i] *= reverseSize;
            }
        }
    }

}

template <typename It>
void multiply(const It fBegin, const It fEnd, const It sBegin, const It sEnd, It res) {
    initPrimeFFT();
    unsigned long fLen = fEnd - fBegin;
    unsigned long sLen = sEnd - sBegin;
    int resLen = fLen + sLen - 1;
    if (resLen <= 100) {
        fill(res, res + resLen, 0);
        for (int i = 0; i < fLen; i++) {
            for (int j = 0; j < sLen; j++) {
                res[i + j] += fBegin[i] * sBegin[j];
            }
        }
        return;
    }
    int resultSize = 1;
    while (resultSize < resLen) {
        resultSize *= 2;
    }
    vector<modint>& aa = prime_fft::aa;
    vector<modint>& bb = prime_fft::bb;
    if (aa.size() < resultSize) {
        aa.resize(resultSize);
        bb.resize(resultSize);
    }
    fill(aa.begin() + fLen, aa.begin() + resultSize, modint(0));
    fill(bb.begin() + sLen, bb.begin() + resultSize, modint(0));
    copy(fBegin, fEnd, aa.begin());
    copy(sBegin, sEnd, bb.begin());
    prime_fft::primeFFT(aa, false, resultSize);
    if (equal(fBegin, fEnd, sBegin, sEnd)) {
        copy(all(aa), bb.begin());
    } else {
        prime_fft::primeFFT(bb, false, resultSize);
    }
    for (int i = 0; i < resultSize; i++) {
        aa[i] *= bb[i];
    }
    prime_fft::primeFFT(aa, true, resultSize);
    for (int i = 0; i < resLen; i++) {
        res[i] = aa[i];
    }
}

vector<modint> multiply(vector<modint>& first, vector<modint>& second) {
    auto len = first.size() + second.size() - 1;
    vector<modint> res(len);
    multiply(all(first), all(second), res.begin());
    return res;
}
