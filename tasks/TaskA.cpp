#include "../lib/io/input.h"
#include "../lib/io/output.h"

//#pragma comment(linker, "/STACK:200000000")

class TaskA {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int c = in.readInt();
        int sum = in.readInt();
        int low = sum / c;
        int high = low + 1;
        int qHigh = sum % c;
        int qLow = c - qHigh;
        int answer = qLow * low * low + qHigh * high * high;
        out.printLine(answer);
	}
};
