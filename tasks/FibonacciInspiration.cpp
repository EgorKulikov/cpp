#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/numbers/modulo.h"
#include "../lib/numbers/matrix.h"

class FibonacciInspiration {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        ll a = in.readLong();
        ll b = in.readLong();
        ll c = in.readLong();
        ll d = in.readLong();
        ll e = in.readLong();
        ll n = in.readLong();
        Matrix<ModuloInt> matrix(5, 5);
        matrix[0][1] = 1;
        matrix[1][2] = 1;
        matrix[2][3] = 1;
        matrix[4][4] = 1;
        matrix[3][0] = d;
        matrix[3][1] = c;
        matrix[3][2] = b;
        matrix[3][3] = a;
        matrix[3][4] = e;
        const auto& answer = matrix.power(n - 1);
        ModuloInt result = answer[0][1] + 2 * answer[0][2] + 3 * answer[0][3] + answer[0][4];
        out.printLine(result);
	}
};
