#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"

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

    program(const vector<ll> &mem) {
        for (int i : Range(mem.size())) {
            this->mem[i] = mem[i];
        }
    }

    pair<state, vector<ll> > run(const vector<ll>& inputs) {
        vector<ll> result;
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
                int first = firstMode ? mem[at + 1] : mem[mem[at + 1]];
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
        vector<ll> mem;
        while (!sin.isExhausted()) {
            mem.push_back(sin.readLong());
        }

        auto p = program(mem);
        auto res = p.run({ll(2)});
        if (res.first != FINISHED) {
            cerr << res.first << endl;
        }
        for (ll r : res.second) {
            out.printLine(r);
        }
	}
};