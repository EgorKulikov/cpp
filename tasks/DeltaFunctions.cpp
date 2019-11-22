#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/numbers/modulo.h"

//#pragma comment(linker, "/STACK:200000000")

class DeltaFunctions {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        vector<ModuloInt> delta(n + 1);
        ModuloInt answer = 0;
        for (int i = 1; i <= n; i++) {
            ModuloInt dif = 1 - delta[i];
            ModuloInt sum = 0;
            for (int j = 1; i * j <= n; j++) {
                sum += j;
            }
            answer += sum * sum * dif;
            for (int j = 2; i * j <= n; j++) {
                delta[i * j] += dif * j * j;
            }
        }
        out.printLine(answer);
	}
};
