#include "../lib/io/input.h"
#include "../lib/io/output.h"

//#pragma comment(linker, "/STACK:200000000")

class Zoos {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        string w = in.readString();
        out.printLine(count(all(w), 'z') * 2 == count(all(w), 'o') ? "Yes" : "No");
	}
};
