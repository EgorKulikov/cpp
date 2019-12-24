#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"

//#pragma comment(linker, "/STACK:200000000")

class TaskD {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        out.printLine("a");
        out.flush();
        int n = in.readInt() + 1;
        if (n == 1) {
            return;
        }
        string s(n, 'a');
        out.printLine(s);
        out.flush();
        int error = in.readInt();
        if (error == n) {
            out.printLine(string(n - 1, 'b'));
            out.flush();
            in.readInt();
            return;
        }
        for (int i : range(n)) {
            s[i] = 'b';
            out.printLine(s);
            out.flush();
            int ne = in.readInt();
            if (ne >= error) {
                s[i] = 'a';
            } else {
                error = ne;
            }
            if (error == 0) {
                return;
            }
        }
	}
};
