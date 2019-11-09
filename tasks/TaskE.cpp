#include "../lib/io/input.h"
#include "../lib/io/output.h"

struct ship {
    int x, y, z, r, id;

    ship(int x, int y, int z, int r, int id) : x(x), y(y), z(z), r(r), id(id) {}
};

bool operator <(const ship& a, const ship& b) {
    return a.r > b.r;
}

class TaskE {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        vector<ship> ships;

        for (int i = 0; i < n; ++i) {
            int x = in.readInt();
            int y = in.readInt();
            int z = in.readInt();
            int r = in.readInt();
            ships.emplace_back(x, y, z, r, i + 1);
        }
        sort(all(ships));
        
        vector<bool> removed(n);
        vi answer;
        for (int i = 0; i < n; i++) {
            if (removed[i]) {
                continue;
            }
            answer.push_back(ships[i].id);
            for (int j = i + 1; j < n; j++) {
                if (removed[j]) {
                    continue;
                }
                removed[j] = hypot(hypot(ships[i].x - ships[j].x, ships[i].y - ships[j].y), ships[i].z - ships[j].z) < ships[i].r + ships[j].r - 1e-8;
            }
        }
        out.printLine(answer.size());
        out.printLine(answer);
	}
};
