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
        arr<string> progr = {"A,B,A,C,A,B,C,B,C,B", "R,10,R,10,R,6,R,4", "R,10,R,10,L,4", "R,4,L,4,L,10,L,10", "n"};
        vec<ll> inps;
        for (const auto& s : progr) {
            for (char c : s) {
                inps.push_back(c);
            }
            inps.push_back(10);
        }
        auto res = p.run(inps);
        if (res.first != FINISHED) {
            cerr << "******" << endl;
        }
        cerr << res.second.size() << endl;
        vec<vec<char>> map(1);
        for (ll i : res.second) {
            if (i >= 256) {
                continue;
            }
            if (i == 10) {
                map.emplace_back();
            } else {
                map.back().push_back(char(i));
            }
        }
        while (map.back().empty()) {
            map.pop_back();
        }
        int n = 39;
        int m = map[0].size();
        int sr = -1, sc;
        for (int i : range(n)) {
            for (int j : range(m)) {
                if (map[i][j] == '^') {
                    sr = i;
                    sc = j;
                }
            }
        }
        int dir = 2;
        vi program;
        int r = sr;
        int c = sc;
        while (true) {
            int nr = r + DX4[dir];
            int nc = c + DY4[dir];
            if (isValidCell(nr, nc, n, m) && map[nr][nc] == '#') {
                program.back()++;
                r = nr;
                c = nc;
                continue;
            }
            nr = r + DX4[(dir + 3) & 3];
            nc = c + DY4[(dir + 3) & 3];
            if (isValidCell(nr, nc, n, m) && map[nr][nc] == '#') {
                program.push_back(-1);
                program.push_back(0);
                dir = (dir + 3) & 3;
                continue;
            }
            nr = r + DX4[(dir + 1) & 3];
            nc = c + DY4[(dir + 1) & 3];
            if (isValidCell(nr, nc, n, m) && map[nr][nc] == '#') {
                program.push_back(-2);
                program.push_back(0);
                dir = (dir + 1) & 3;
                continue;
            }
            break;
        }
        for (const auto& row : map) {
            out.printLine(string(all(row)));
        }
        out.printLine(program);
        out.printLine(res.second.back());
	}
};
