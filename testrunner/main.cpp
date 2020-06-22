#include "../tasks/AMaksimalniiNOD.cpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <ctime>
#include "../lib/general.h"

namespace jhelper {

struct Test {
	std::string input;
	std::string output;
	bool active;
	bool has_output;
};

bool check(std::string expected, std::string actual) {
	while(!expected.empty() && isspace(*--expected.end()))
		expected.erase(--expected.end());
	while(!actual.empty() && isspace(*--actual.end()))
		actual.erase(--actual.end());
	return expected == actual;
}

} // namespace jhelper

int main() {
    string blue = "\x1B[34m";
    string red = "\x1B[31m";
    string green = "\x1B[32m";
    string yellow = "\x1B[33m";
    string def = "\033[0m";
    std::vector<jhelper::Test> tests = {
		{"2\n3\n5\n", "1\n2\n", true, true},
	};
	bool allOK = true;
	int testID = 0;
	std::cout << std::fixed;
	double maxTime = 0.0;
	for(const jhelper::Test& test: tests ) {
		std::cout << blue << "Test #" << ++testID << def << std::endl;
		if (!test.active) {
            std::cout << yellow << "SKIPPED\n" << def;
            std::cout << std::endl;
            continue;
		}
		std::cout << blue << "Input: \n" << def << test.input << std::endl;
		if (test.has_output) {
			std::cout << blue << "Expected output: \n" << def << test.output << std::endl;
		}
		else {
			std::cout << blue << "Expected output: \n" << def << yellow << "N/A" << def << std::endl;
		}
		if (test.active) {
            std::ofstream inw;
            inw.open("jhelperinput.txt");
            inw << test.input;
            inw.close();
            freopen("jhelperinput.txt", "r", stdin);
            ofstream fout("jhelperoutput.txt");
            std::clock_t start = std::clock();
            try {
                in = Input();
                out.setOut(fout);
                AMaksimalniiNOD solver;
                int n;
scanf("%d", &n);
for(int i = 0; i < n; ++i) {
	solver.solve();
}

                out.flush();
                fout.close();
            } catch (const char* e) {
                std::cerr << e << std::endl;
            }
            if (!in.isExhausted() && in.skipWhitespace() != EOF) {
                cout << red << "Input is not exhausted" << def << endl;
            }
            std::clock_t finish = std::clock();
            double currentTime = double(finish - start) / CLOCKS_PER_SEC;
            maxTime = std::max(currentTime, maxTime);
            std::ifstream t("jhelperoutput.txt");
            std::stringstream output;
            output << t.rdbuf();
            std::cout << blue << "Actual output: \n" << def << output.str() << std::endl;
            if (test.has_output) {
                bool result = jhelper::check(test.output, output.str());
                allOK = allOK && result;
                std::cout << blue << "Result: " << def << (result ? green + "OK" : red + "Wrong answer") << def << std::endl;
            }
            std::cout << blue << "Time: " << int(currentTime) << "." << (int(currentTime * 10) % 10) << (int(currentTime * 100) % 10) << (int(currentTime * 1000) % 10) << "s" << def << std::endl;
            t.close();
		}

		std::cout << std::endl;
	}
	if (allOK) {
		std::cout << green << "All OK" << def << std::endl;
	} else {
		std::cout << red << "Some cases failed" << def << std::endl;
	}
	std::cout << blue << "Maximal time: " << int(maxTime) << "." << (int(maxTime * 10) % 10) << (int(maxTime * 100) % 10) << (int(maxTime * 1000) % 10) << "s" << def << std::endl;
	return 0;
}
