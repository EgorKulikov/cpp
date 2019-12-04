#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/numbers/primes.h"

//#pragma comment(linker, "/STACK:200000000")

vi p = primes(1000);

class HowManyPrimesDivideTheNumber {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();

        int answer = 0;
        for (int i : p) {
            if (n % i == 0) {
                answer++;
            }
        }
        out.printLine(answer);
	}
};
