#include <array>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>

#include <unistd.h>

#include "movingAverage.h"
#include "profiler.h"

static std::array<float, 1000000> inputFloats;
static std::array<float, 1000000> outputFloats;

static std::array<double, 1000000> inputDoubles;
static std::array<double, 1000000> outputDoubles;

template<typename TInput, typename TOutput>
void performanceTest(const char *name, TInput& inputData, TOutput& outputData, size_t frameSize)
{
	profiler::Profiler profiler{name};

	movingAverage::computeMovingAverage(inputData, outputData, frameSize);
}

int main(int argc, const char* argv[])
{
	std::cout << "Quick test" << std::endl;

	movingAverage::fillTestData(inputFloats);

	performanceTest("quick_test_floats_4", inputFloats, outputFloats, 4);

	movingAverage::dump(outputFloats, "floats_quick_test.txt");

	movingAverage::fillTestData(inputDoubles);

	performanceTest("quick_test_doubles_4", inputDoubles, outputDoubles, 4);

	movingAverage::dump(outputDoubles, "doubles_quick_test.txt");

	std::cout << "Quick test done !" << std::endl;

	std::cout << "Floats performance test" << std::endl;

	movingAverage::fillRandomData(inputFloats);

	performanceTest("floats_4", inputFloats, outputFloats, 4);
	performanceTest("floats_8", inputFloats, outputFloats, 8);
	performanceTest("floats_16", inputFloats, outputFloats, 16);
	performanceTest("floats_32", inputFloats, outputFloats, 32);
	performanceTest("floats_64", inputFloats, outputFloats, 64);
	performanceTest("floats_128", inputFloats, outputFloats, 128);

	std::cout << "Floats performance test done !" << std::endl;

	std::cout << "Doubles performance test" << std::endl;

	movingAverage::fillRandomData(inputDoubles);

	performanceTest("doubles_4", inputDoubles, outputDoubles, 4);
	performanceTest("doubles_8", inputDoubles, outputDoubles, 8);
	performanceTest("doubles_16", inputDoubles, outputDoubles, 16);
	performanceTest("doubles_32", inputDoubles, outputDoubles, 32);
	performanceTest("doubles_64", inputDoubles, outputDoubles, 64);
	performanceTest("doubles_128", inputDoubles, outputDoubles, 128);

	std::cout << "Doubles performance test done !" << std::endl;

	profiler::Profiler::dump("results.txt");

	return 0;
}
