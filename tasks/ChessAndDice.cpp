#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/numbers/rational.h"

class ChessAndDice {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        Rational c = 0;
        Rational a = 0;
        for (int i = n - 1; i >= 0; i--) {
            c = 1 + Rational(2, 7) * c;
            a = Rational(2, 7) * a + Rational(5, 7);
        }
        Rational answer = c / (1 - a);
        out.printLine(answer.num + answer.den);
	}
};
