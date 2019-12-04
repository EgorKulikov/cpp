#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"

//#pragma comment(linker, "/STACK:200000000")

class MyLongestPalindrome {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        in.readInt();
        string s = in.readString();
        vi qty(26);
        for (char c : s) {
            qty[c - 'A']++;
        }
        vector<char> answer;
        for (int i : Range(26)) {
            for (int j : Range(qty[i] / 2)) {
                answer.push_back(i + 'A');
            }
        }
        string back(all(answer));
        reverse(all(back));
        for (int i : Range(26)) {
            if (qty[i] % 2 == 1) {
                answer.push_back(i + 'A');
                break;
            }
        }
        string res(all(answer));
        res += back;
        out.printLine(res);
	}
};
