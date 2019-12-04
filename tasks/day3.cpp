#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"

//#pragma comment(linker, "/STACK:200000000")

class day3 {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        auto build = [](const string& s) -> vector<pii> {
            int x = 0;
            int y = 0;
            vector<pii> res;
            string ss = s;
            replace(all(ss), ',', ' ');
            istringstream inp(ss);
            Input in(inp);

            while (!in.isExhausted()) {
                char direction = in.readType<char>();
                int length = in.readInt();
                int dx = 0, dy = 0;
                if (direction == 'U') {
                    dy = 1;
                } else if (direction == 'D') {
                    dy = -1;
                } else if (direction == 'R') {
                    dx = 1;
                } else {
                    dx = -1;
                }
                for (int i : Range(length)) {
                    x += dx;
                    y += dy;
                    res.emplace_back(x, y);
                }
            }
            return res;
        };
        
        auto first = build(in.readString());
        auto second = build(in.readString());
        
        map<pii, int> path;
        for (int i : Range(first.size())) {
            if (path[first[i]] == 0) {
                path[first[i]] = i + 1;
            }
        }
        int answer = numeric_limits<int>::max();
        for (int i : Range(second.size())) {
            if (path.count(second[i])) {
                minim(answer, path[second[i]] + i + 1);
            }
        }
        out.printLine(answer);
	}
};
