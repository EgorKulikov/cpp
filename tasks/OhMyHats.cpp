#include "../lib/io/input.h"
#include "../lib/io/output.h"

using namespace std;

class OhMyHats {
public:
	void solve(std::istream& inp, std::ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        int v = sqrt(n - 1);
        while (v * v > n - 1) {
            v--;
        }
        while ((v + 1) * (v + 1) <= n - 1) {
            v++;
        }
        out.printLine(v + n % 2);
	}
};
