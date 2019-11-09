#include "../lib/io/input.h"
#include "../lib/io/output.h"

class TaskB {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        int m = in.readInt();
        auto start = in.readType<double>();
        auto d = in.readTable<double>(m, n);
        
        for (int i = 0; i < n - 1; i++) {
            double ratio = 1;
            for (int j = 0; j < m; j++) {
                maxim(ratio, d[j][i + 1] / d[j][i]);
            }
            start *= ratio;
        }
        outp << fixed << setprecision(2);
        out.printLine(start);
	}
};
