#include "../lib/io/input.h"
#include "../lib/io/output.h"

//#pragma comment(linker, "/STACK:200000000")

class AnotherEnclosedRegion {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        unordered_map<char, int> q = {
                {'A', 1},
                {'B', 2},
                {'D', 1},
                {'O', 1},
                {'P', 1},
                {'Q', 1},
                {'R', 1}
        };
        string s = in.readString();
        int answer = 0;
        for (char c : s) {
            answer += q[c];
        }
        out.printLine(answer);
	}
};
