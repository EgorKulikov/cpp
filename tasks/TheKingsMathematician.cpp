#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/numbers/modulo.h"

//#pragma comment(linker, "/STACK:200000000")

int id = 1;

class TheKingsMathematician {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        mod = n;
        int a = in.readInt();
        int c = in.readInt();

        vector<bool> vis(n);
        ModuloInt cur = 0;
        while (!vis[cur.n]) {
            vis[cur.n] = true;
            cur = cur * a + c;
        }
        out.print("Case #");
        out.print(id++);
        out.printLine(':', count(all(vis), true));
	}
};
