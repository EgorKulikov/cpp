#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/algo.h"

class AntScheduling {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        vector<pair<int, int> > left;
        vector<pair<int, int> > right;

        for (int i = 0; i < n; ++i) {
            char direction = in.readType<char>();
            int a = in.readInt();
            int t = in.readInt();
            if (direction == 'L') {
                left.emplace_back(a, t);
            } else {
                right.emplace_back(a, t);
            }
        }

        sort(all(left));
        sort(all(right));
        auto ansLeft = makeArray<int>(left.size() + 1, right.size() + 1, 1000000000);
        auto ansRight = makeArray<int>(left.size() + 1, right.size() + 1, 1000000000);

        ansLeft[0][0] = ansRight[0][0] = 0;

        for (int i = 0; i <= left.size(); i++) {
            for (int j = 0; j <= right.size(); j++) {
                int start = ansRight[i][j] - 10;
                int end = start;
                for (int l = i; l < left.size(); l++) {
                    start = max(start + 10, left[l].first);
                    end = max(end + 10, start + left[l].second);
                    minim(ansLeft[l + 1][j], end);
                }
                start = ansLeft[i][j] - 10;
                end = start;
                for (int l = j; l < right.size(); l++) {
                    start = max(start + 10, right[l].first);
                    end = max(end + 10, start + right[l].second);
                    minim(ansRight[i][l + 1], end);
                }
            }
        }
        out.printLine(min(ansLeft[left.size()][right.size()], ansRight[left.size()][right.size()]));
	}
};
