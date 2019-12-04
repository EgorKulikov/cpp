#include "../lib/io/input.h"
#include "../lib/io/output.h"

//#pragma comment(linker, "/STACK:200000000")

class Div3Roman {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        string s = in.readString();
        int lastDigit = 0;
        int answer = 0;
        unordered_map<char, int> value = {
                {'I', 1},
                {'V', 5},
                {'X', 10},
                {'L', 50},
                {'C', 100},
                {'D', 500},
                {'M', 1000}
        };
        for (char c : s) {
            int v = value[c];
            if (v > lastDigit) {
                answer -= 2 * lastDigit;
            }
            answer += v;
            lastDigit = v;
        }
        out.printLine(answer % 3 == 0 ? "YES" : "NO", answer);
	}
};
