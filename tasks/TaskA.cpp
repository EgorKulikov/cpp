#include "../lib/io/input.h"
#include "../lib/io/output.h"

class TaskA {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        int answer = 0;
        for (int i = 0; i < n; ++i) {
            string s = in.readString();
            string ss = s;
            reverse(all(ss));
            if (s == ss) {
                answer++;
            }
        }
        out.printLine(answer);
	}
};
