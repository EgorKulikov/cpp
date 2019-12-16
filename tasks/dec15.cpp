#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"

//#pragma comment(linker, "/STACK:200000000")

class dec15 {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        arr<string> s(n);
        for (int i : range(n)) {
            s[i] = in.readLine();
        }

        arri q(26, 0);
        int sum = 0;
        for (const auto& ss : s) {
            arri qq(26, 0);
            int ssum = 0;
            for (char c : ss) {
                if (c != ' ') {
                    q[c - 'a']++;
                    qq[c - 'a']++;
                    sum += c - 'a';
                    ssum += c - 'a';
                }
            }
            out.printLine(ssum, ssum % 26, accumulate(all(qq), 0), 26 - count(all(qq), 0));
            out.printLine(qq);
        }
        out.printLine(sum, sum % 26, accumulate(all(q), 0), 26 - count(all(q), 0));
        out.printLine(q);
	}
};
