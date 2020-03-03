#include "C:/Users/egor/proj/cpp/tasks/DMOPC19Contest5P6CeciliasComputationalCrisis.cpp"

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
	std::vector<jhelper::Test> tests = {
		{"4 4\n.?XX\n?X..\n.??X\nXX..\n", "YES\n.XXX\n.X..\n.X.X\nXX..\n", true, true},{"5 5\n.X?X?\n.X..X\n.XX.X\n?.???\n.X?.X\n", "NO\n", true, true},{"4 2\n??\n??\n??\n??\n", "", true, false},
	};
	bool allOK = true;
	int testID = 0;
	std::cout << std::fixed;
	double maxTime = 0.0;
	for(const jhelper::Test& test: tests ) {
		std::cout << "Test #" << ++testID << std::endl;
		std::cout << "Input: \n" << test.input << std::endl;
		if (test.has_output) {
			std::cout << "Expected output: \n" << test.output << std::endl;
		}
		else {
			std::cout << "Expected output: \n" << "N/A" << std::endl;
		}
		if (test.active) {
			std::stringstream in(test.input);
			std::ostringstream out;
			std::clock_t start = std::clock();
			try {
			    DMOPC19Contest5P6CeciliasComputationalCrisis solver;
			    solver.solve(in, out);
            } catch (const char* e) {
                std::cerr << e << std::endl;
            }
			std::clock_t finish = std::clock();
			double currentTime = double(finish - start) / CLOCKS_PER_SEC;
			maxTime = std::max(currentTime, maxTime);
			std::cout << "Actual output: \n" << out.str() << std::endl;
			if (test.has_output) {
				bool result = jhelper::check(test.output, out.str());
				allOK = allOK && result;
				std::cout << "Result: " << (result ? "OK" : "Wrong answer") << std::endl;
			}
			std::cout << "Time: " << currentTime << std::endl;
		}
		else {
			std::cout << "SKIPPED\n";
		}

		std::cout << std::endl;

	}
	if(allOK) {
		std::cout << "All OK" << std::endl;
	}
	else {
		std::cout << "Some cases failed" << std::endl;
	}
	std::cout << "Maximal time: " << maxTime << "s." << std::endl;
	return 0;
}
