#include "../lib/io/input.h"
#include "../lib/io/output.h"

//#pragma comment(linker, "/STACK:200000000")

class DMOPC19Contest3P1ModeFinding {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        auto a = in.readIntArray(n);
        
        unordered_map<int, int> map;
        for (int i : a) {
            map[i]++;
        }
        int qty = 0;
        vi answer;
        for (const auto& p : map) {
            if (p.second > qty) {
                qty = p.second;
                answer.clear();
            }
            if (p.second == qty) {
                answer.push_back(p.first);
            }
        }
        sort(all(answer));
        out.printLine(answer);
	}
};
