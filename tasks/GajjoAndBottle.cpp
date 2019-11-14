#include "../lib/io/input.h"
#include "../lib/io/output.h"

class GajjoAndBottle {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        string s = in.readString();
        string t = in.readString();
        vector<bool> a(26);
        vector<bool> b(26);

        for (char c : s) {
            a[c - 'a'] = true;
        }
        for (char c : t) {
            b[c - 'a'] = true;
        }
        vector<char> answer;
        for (char c : s) {
            if (!b[c - 'a']) {
                answer.push_back(c);
            }
        }
        for (char c : t) {
            if (!a[c - 'a']) {
                answer.push_back(c);
            }
        }
        string ans(all(answer));
        if (ans.empty()) {
            out.printLine(-1);
        } else {
            out.printLine(ans);
        }
	}
};
