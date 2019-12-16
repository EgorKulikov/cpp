#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"
#include "../lib/misc.h"
#include "../lib/collections/queue.h"

//#pragma comment(linker, "/STACK:200000000")

enum state {
    FINISHED,
    WAITING,
    CRASHED
};

struct program {
    map<ll, ll> mem;
    ll at = 0;
    ll rel = 0;

    program(const vec<ll> &mem) {
        for (int i : range(mem.size())) {
            this->mem[i] = mem[i];
        }
    }

    pair<state, vec<ll> > run(const vec<ll>& inputs) {
        vec<ll> result;
        int inAt = 0;
        auto get = [&](ll at, int mode) -> ll& {
            if (mode == 0) {
                return mem[mem[at]];
            } else if (mode == 1) {
                return mem[at];
            } else {
                return mem[mem[at] + rel];
            }
        };
        while (true) {
            int op = mem[at] % 100;
            int firstMode = mem[at] / 100 % 10;
            int secondMode = mem[at] / 1000 % 10;
            int thirdMode = mem[at] / 10000 % 10;
            if (op == 99) {
                return make_pair(FINISHED, result);
            }
            if (op == 1) {
                get(at + 3, thirdMode) = get(at + 1, firstMode) + get(at + 2, secondMode);
                at += 4;
            } else if (op == 2) {
                get(at + 3, thirdMode) = get(at + 1, firstMode) * get(at + 2, secondMode);
                at += 4;
            } else if (op == 3) {
                if (inAt == inputs.size()) {
                    return make_pair(WAITING, result);
                }
                get(at + 1, firstMode) = inputs[inAt++];
                at += 2;
            } else if (op == 4) {
                result.push_back(get(at + 1, firstMode));
                at += 2;
            } else if (op == 5) {
                if (get(at + 1, firstMode) != 0) {
                    at = get(at + 2, secondMode);
                } else {
                    at += 3;
                }
            } else if (op == 6) {
                if (get(at + 1, firstMode) == 0) {
                    at = get(at + 2, secondMode);
                } else {
                    at += 3;
                }
            } else if (op == 7) {
                get(at + 3, thirdMode) = get(at + 1, firstMode) < get(at + 2, secondMode) ? 1 : 0;
                at += 4;
            } else if (op == 8) {
                get(at + 3, thirdMode) = get(at + 1, firstMode) == get(at + 2, secondMode) ? 1 : 0;
                at += 4;
            } else if (op == 9) {
                rel += get(at + 1, firstMode);
                at += 2;
            } else {
                return make_pair(CRASHED, result);
            }
        }
    }
};

class day2 {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        string input = in.readString();
        replace(all(input), ',', ' ');
        istringstream str(input);
        Input sin(str);
        vec<ll> mem;
        while (!sin.isExhausted()) {
            mem.push_back(sin.readLong());
        }
        auto p = program(mem);
        arri comm = {4, 1, 3, 2};
        int x = 0;
        int y = 0;
        map<pii, char> m;
        int dist = 0;
        vi order;
        m[{0, 0}] = 's';
        int ex, ey;
        auto printMap = [&]() {
            int mix = numeric_limits<int>::max();
            int max = numeric_limits<int>::min();
            int miy = numeric_limits<int>::max();
            int may = numeric_limits<int>::min();
            for (const auto& p : m) {
                minim(mix, p.first.first);
                maxim(max, p.first.first);
                minim(miy, p.first.second);
                maxim(may, p.first.second);
            }
            vec<string> answer(may - miy + 1, string(max - mix + 1, '?'));
            for (const auto& p : m) {
                answer[p.first.second - miy][p.first.first - mix] = p.second;
            }
            for (const auto& row : answer) {
                out.printLine(row);
            }
        };
        while (true) {
            bool move = false;
            for (int i : range(4)) {
                int nx = x + DX4[i];
                int ny = y + DY4[i];
                if (m.count({nx, ny}) == 0) {
                    auto pair = p.run({comm[i]});
                    if (pair.first != WAITING || pair.second.size() != 1) {
                        cerr << "********" << endl;
                    }
                    int res = pair.second[0];
                    if (res == 0) {
                        m[{nx, ny}] = '#';
                        continue;
                    }
                    if (res == 2) {
                        m[{nx, ny}] = 't';
                        cerr << dist + 1 << endl;
//                        out.printLine(dist + 1);
                        ex = nx;
                        ey = ny;
                    } else {
                        m[{nx, ny}] = '.';
                    }
                    order.push_back(i);
                    dist++;
                    x = nx;
                    y = ny;
                    move = true;
                    break;
                }
            }
            if (!move) {
                if (order.empty()) {
                    printMap();
                    break;
                }
                int i = order.back();
                x -= DX4[i];
                y -= DY4[i];
                p.run({comm[i ^ 2]});
                dist--;
                order.pop_back();
            }
        }
        que<pii> q;
        q.push({ex, ey});
        map<pii, int> dst;
        dst[{ex, ey}] = 0;
        int answer = 0;
        while (!q.empty()) {
            int x, y;
            tie(x, y) = q.pop();
            maxim(answer, dst[{x, y}]);
            for (int i : range(4)) {
                int nx = x + DX4[i];
                int ny = y + DY4[i];
                if (m[{nx, ny}] == '#' || dst.count({nx, ny})) {
                    continue;
                }
                dst[{nx, ny}] = dst[{x, y}] + 1;
                q.push({nx, ny});
            }
        }
        out.printLine(answer);
	}
};
