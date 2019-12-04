#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/collections/interval_tree.h"
#include "../lib/collections/fenwick.h"

//#pragma comment(linker, "/STACK:200000000")

class DMOPC19Contest3P5Festival {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        const int BUBEN = 1000;

        int n = in.readInt();
        int q = in.readInt();
        auto c = in.readArray<ll>(n);
        vi type;
        vector<ll> value;
        in.readArrays(q, type, value);

        ll start = *min_element(all(c));
        ll end = *max_element(all(c));
        ll delta = 0;
        for (int i = 0; i < q; ++i) {
            if (type[i] == 1) {
                ll current = value[i] - delta;
                minim(start, current);
                maxim(end, current);
            } else if (type[i] == 2) {
                delta += value[i];
            }
        }

        int range = end - start;
        /*vector<ll> leftTree(4 * range);
        vector<ll> rightTree(4 * range);
        vector<int> qt(4 * range);

        function<void(int, int, int, int)> add = [&](int root, int left, int right, int at) -> void {
            if (left > at || right <= at) {
                return;
            }
            if (left + 1 == right) {
                leftTree[at] += left;
                rightTree[at] += range - at;
                qt[at]++;
                return;
            }
            int mid = (left + right) >> 1;
            add(2 * root + 1, left, mid, at);
            add(2 * root + 2, mid, right, at);
            leftTree[root] = leftTree[2 * root + 1] + leftTree[2 * root + 2];
            rightTree[root] = rightTree[2 * root + 1] + rightTree[2 * root + 2];
            qt[root] = qt[2 * root + 1] + qt[2 * root + 2];
        };*/
        FenwickTree leftTree(range + 1);
        FenwickTree rightTree(range + 1);
        FenwickTree qt(range + 1);
//
/*        auto llSum = [](ll a, ll b) -> ll { return a + b; };
        auto intSum = [](int a, int b) -> int { return a + b; };
        auto leftAccum = [](ll a, int b, int left, int) -> ll { return a + ll(b) * left; };
        auto rightAccum = [range](ll a, int b, int left, int) -> ll { return a + ll(b) * (range - left); };
        auto qtAccum = [](int a, int b, int, int) -> int { return a + b; };
        IntervalTree<ll, int> leftTree(range + 1, llSum, intSum, leftAccum);
        IntervalTree<ll, int> rightTree(range + 1, llSum, intSum, rightAccum);
        IntervalTree<int, int> qt(range + 1, intSum, intSum, qtAccum);*/

        for (ll val : c) {
            leftTree.add(val - start, val - start);
            rightTree.add(val - start, range - (val - start));
            qt.add(val - start, 1);
        }

        auto llQuery = [&](FenwickTree& tree, ll from, ll to) -> ll {
            return tree.get(max(ll(0), min(ll(range + 1), from)), max(ll(0), min(ll(range + 1), to)));
        };

        delta = 0;
        for (int i = 0; i < q; ++i) {
            if (type[i] == 1) {
                ll val = value[i] - delta;
                c.push_back(val);
                leftTree.add(val - start, val - start);
                rightTree.add(val - start, range - (val - start));
                qt.add(val - start, 1);
            } else if (type[i] == 2) {
                delta += value[i];
            } else if (type[i] == 3) {
                ll mod = value[i];
                if (mod <= BUBEN) {
                    ll answer = 0;
                    for (ll val : c) {
                        ll rem = (val + delta) % mod;
                        rem = abs(rem);
                        answer += min(rem, mod - rem);
                    }
                    out.printLine(answer);
                } else {
                    ll rem = (start + delta) % mod;
                    rem = -rem;
                    if (rem > 0) {
                        rem -= mod;
                    }
                    ll answer = 0;
                    ll half = mod / 2 + 1;
                    while (rem < range) {
                        ll leftQuery = llQuery(leftTree, rem, rem + half);
                        int leftQty = llQuery(qt, rem, rem + half);
                        answer += leftQuery - leftQty * rem;
                        ll rightQuery = llQuery(rightTree, rem + half, rem + mod);
                        int rightQty = llQuery(qt, rem + half, rem + mod);
                        answer += rightQuery - rightQty * (range - (rem + mod));
                        rem += mod;
                    }
                    out.printLine(answer);
                }
            }
        }
	}
};
