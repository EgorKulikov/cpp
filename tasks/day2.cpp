#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"
#include "../lib/misc.h"

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
        for (int i : Range(mem.size())) {
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
        vec<ll> mem;
        while (!sin.isExhausted()) {
            mem.push_back(sin.readLong());
        }
        auto p = program(mem);
        vec<ll> inputs;
        ll score = 0;
        while (true) {
            map<pii, int> hull;
            auto res = p.run(inputs);
            if (res.first == CRASHED) {
                cerr << "******" << endl;
            }
            auto vec = res.second;
            for (int i = 0; i < vec.size(); i += 3) {
                if (vec[i] == -1 && vec[i + 1] == 0) {
                    score = vec[i + 2];
                    continue;
                }
                hull[make_pair(vec[i], vec[i + 1])] = vec[i + 2];
            }
            cerr << score << endl;
            int paddlePos;
            int ballPos;
            int numBlocks = 0;

            for (const auto& p : hull) {
                if (p.second == 1) {
                    numBlocks++;
                } else if (p.second == 3) {
                    paddlePos = p.first.first;
                } else if (p.second == 4) {
                    ballPos = p.first.first;
                }
            }
            inputs.clear();
            if (ballPos < paddlePos) {
                inputs.push_back(-1);
            } else if (ballPos > paddlePos) {
                inputs.push_back(1);
            } else {
                inputs.push_back(0);
            }
            if (res.first == FINISHED) {
                break;
            }
        }
        out.printLine(score);
/*        auto res = p.run({});
        int mix = numeric_limits<int>::max();
        int max = numeric_limits<int>::min();
        int miy = numeric_limits<int>::max();
        int may = numeric_limits<int>::min();
        for (const auto& p : hull) {
            minim(mix, p.first.first);
            maxim(max, p.first.first);
            minim(miy, p.first.second);
            maxim(may, p.first.second);
        }
        int r = 0;
        vec<string> answer(may - miy + 1, string(max - mix + 1, ' '));
        for (const auto& p : hull) {
            if (p.second == 1) {
                answer[p.first.second - miy][p.first.first - mix] = 'X';
            } else if (p.second == 2) {
                answer[p.first.second - miy][p.first.first - mix] = '*';
                r++;
            } else if (p.second == 3) {
                answer[p.first.second - miy][p.first.first - mix] = '-';
            } else if (p.second == 4) {
                answer[p.first.second - miy][p.first.first - mix] = 'o';
            }
        }
        for (const auto& row : answer) {
            out.printLine(row);
        }
        out.printLine(r);*/
	}
};
