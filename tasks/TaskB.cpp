#include "../lib/io/input.h"
#include "../lib/io/output.h"

//#pragma comment(linker, "/STACK:200000000")

class TaskB {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int a = in.readInt();
        int b = in.readInt();

        if ((a + b) % 3 == 0 && a <= 2 * b && b <= 2 * a) {
            out.printLine("YES");
        } else {
            out.printLine("NO");
        }
	}
};
