#include "../lib/io/input.h"
#include "../lib/io/output.h"

class TaskD {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int k = in.readInt();
        int n = in.readInt();

        double a = 0;
        double c = 0;
        for (int i = n - 1; i >= 0; i--) {
            c = 1 + c / k;
            a = a / k + double(k - 1) / k;
        }
        double answer = c / (1 - a);
        outp << fixed << setprecision(4);
        out.printLine(answer);
	}
};
