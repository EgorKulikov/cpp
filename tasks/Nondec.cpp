#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"
#include "../lib/numbers/modulo.h"
#include "../lib/range/rev_range.h"
#include "../lib/algo.h"

class Nondec {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        int k = in.readInt();
        auto a = in.readIntArray(n);
        decreaseByOne(a);

        int BUBEN = 200;
        int parts = n / BUBEN + 1;
        arr2d<arr2d<modint>> res(parts, parts);
        arr2d<modint> cur(k, k);
        arr3d<modint> left(parts, BUBEN, k);
        arr2d<modint> shAns(n, BUBEN + 1);
        for (int i : range(parts)) {
            for (int j : range(min(BUBEN, n - i * BUBEN))) {
                for (int l : range(k)) {
                    left(i, j, l) = 0;
                }
                left(i, j, 0) = 1;
                for (int l : range(j, min(BUBEN, n - i * BUBEN))) {
                    for (int m : RevRange(a[l + i * BUBEN] + 1)) {
                        left(i, j, a[l + i * BUBEN]) += left(i, j, m);
                    }
                    shAns(i * BUBEN + j, l - j + 1) = left(i, j, k - 1);
                    for (int m : range(k)) {
                        shAns(i * BUBEN + j, l - j + 1) += left(i, j, m);
                    }
                }
//                for (int l : range(1, k)) {
//                    left(i, j, l) += left(i, j, l - 1);
//                }
            }
        }
        arr3d<modint> right(parts, BUBEN, k);
        for (int i : range(parts)) {
            for (int j : range(min(BUBEN, n - i * BUBEN + 1))) {
                for (int l : range(k - 1)) {
                    right(i, j, l) = 0;
                }
                right(i, j, k - 1) = 1;
                for (int l : RevRange(j)) {
                    for (int m : range(a[l + i * BUBEN], k)) {
                        right(i, j, a[l + i * BUBEN]) += right(i, j, m);
                    }
                    shAns(l + i * BUBEN, j - l) = 0;
                    for (int m : range(k)) {
                        shAns(l + i * BUBEN, j - l) += right(i, j, m);
                    }
                }
            }
        }
        for (int i : range(parts)) {
            res(i, i) = arr2d<modint>(k, k, 0);
//            for (int j : range(k)) {
//                for (int l : range(j, k)) {
//                    res(i, i)(j, l) = 1;
//                }
//            }
        }
        for (int i : range(parts - 1)) {
            fill(all(cur), 0);
//            for (int j : range(k)) {
//                cur(j, j) = 1;
//            }
            for (int j : range(BUBEN)) {
                int id = j + i * BUBEN;
                for (int m : range(0, a[id] + 1)) {
                    modint total = 0;
                    for (int l : range(m, a[id] + 1)) {
                        total += cur(m, l);
                    }
                    cur(m, a[id]) += total;
                }
                cur(a[id], a[id]) += 1;
            }
            for (int j : range(i + 1)) {
                res(j, i + 1) = arr2d<modint>(k, k, 0);
                for (int l : range(k)) {
                    modint sum = 0;
                    for (int m : range(l, k)) {
                        res(j, i + 1)(l, m) += res(j, i)(l, m) + cur(l, m);
                        sum += res(j, i)(l, m);
                        for (int o : range(m, k)) {
                            res(j, i + 1)(l, o) += sum * cur(m, o);
                        }
                    }
//                    for (int m : range(l + 1, k)) {
//                        res(j, i + 1)(l, m) += res(j, i + 1)(l, m - 1);
//                    }
                }
            }
/*            for (int j : range(i * BUBEN, n)) {
                if (j % BUBEN == 0) {
                    int jj = j / BUBEN;
                    res(i, jj) = cur.clone();
                    for (int m : range(k)) {
                        for (int l : range(m + 1, k)) {
                            res(i, jj)(m, l) += res(i, jj)(m, l - 1);
                        }
                    }
                }
//                if (j - i * BUBEN < BUBEN) {
//                    for (int l : range(k)) {
//                        right(i, j - i * BUBEN, l) = cur(l, k - 1);
//                    }
//                }
                for (int m : range(0, a[j] + 1)) {
                    modint total = 0;
                    for (int l : range(m, a[j] + 1)) {
                        total += cur(m, l);
                    }
                    cur(m, a[j]) += total;
                }
//                if (j + 1 == n && j - i * BUBEN + 1 < BUBEN) {
//                    for (int l : range(k)) {
//                        right(i, j - i * BUBEN + 1, l) = cur(l, k - 1);
//                    }
//                }
            }
            if (n % BUBEN == 0) {
                int jj = n / BUBEN;
                res(i, jj) = cur.clone();
                for (int m : range(k)) {
                    for (int l : range(m + 1, k)) {
                        res(i, jj)(m, l) += res(i, jj)(m, l - 1);
                    }
//                    right(jj, 0, m) = 0;
                }
//                right(jj, 0, k - 1) = 1;
            }*/
        }
/*        for (int i : range(parts)) {
            for (int j : range(i, parts)) {
                for (int l : range(k)) {
                    res(i, j)(l, l) += 1;
                    for (int m : range(l + 1, k)) {
                        res(i, j)(l, m) += res(i, j)(l, m - 1);
                    }
                }
            }
        }*/
        int q = in.readInt();
        for (int x : range(q)) {
            int l = in.readInt() - 1;
            int r = in.readInt();
            int lPart = l / BUBEN;
            int lId = l % BUBEN;
            int rPart = r / BUBEN;
            int rId = r % BUBEN;
            if (lPart == rPart) {
                out.printLine(shAns(l, r - l));
            } else {
                modint answer = 0;
                modint sumLeft = 0;
                for (int i : range(k)) {
                    sumLeft += left(lPart, lId, i);
                    modint sumRight = 0;
                    for (int j : RevRange(k, i)) {
                        sumRight += right(rPart, rId, j);
                        answer += sumLeft * res(lPart + 1, rPart)(i, j) * sumRight + left(lPart, lId, i) * right(rPart, rId, j);
                    }
                }
                out.printLine(answer);
            }
        }
/*        int q = in.readInt();
        arri l, r;
        in.readArrays(q, l, r);
        decreaseByOne(l);

        auto order = createOrder(q);
        sort(all(order), [&](int x, int y) -> bool {
            return r[x] < r[y];
        });
        int at = 0;
        arr<modint> answer(q);
        arr2d<modint> cur(parts, k);
        int to = 0;
        for (int i : range(n)) {
            if (i % BUBEN == 0) {
                for (int j : range(k)) {
                    cur(to, j) = 0;
                }

            }
        }*/
	}
};
