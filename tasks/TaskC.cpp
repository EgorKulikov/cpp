#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"

//#pragma comment(linker, "/STACK:200000000")

class TaskC {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        int t = in.readInt();
        int a = in.readInt();
        int b = in.readInt();
        auto type = in.readIntArray(n);
        auto time = in.readIntArray(n);

        arr<pair<int, bool>> tasks(n);
        for (int i : range(n)) {
            tasks[i] = {time[i], type[i] == 1};
        }
        sort(all(tasks));
        int easy = count(all(type), 0);
        int hard = count(all(type), 1);
        int answer = 0;
        ll spent = 0;
        int at = 0;
        for (const auto& t : tasks) {
            int until = t.first - 1;
            if (spent <= until) {
                int rem = until - spent;
                int mEasy = min(easy, rem / a);
                rem -= mEasy * a;
                int mHard = min(hard, rem / b);
                maxim(answer, at + mEasy + mHard);
            }
            spent += t.second ? b : a;
            if (t.second) {
                hard--;
            } else {
                easy--;
            }
            at++;
        }
        if (spent <= t) {
            answer = n;
        }
        out.printLine(answer);
	}
};
