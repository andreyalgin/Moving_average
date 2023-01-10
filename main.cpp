#include <array>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>

#include <unistd.h>

using Input = std::array<float, 64>;
using Output = std::array<float, 49>;

static Input inputData;
static Output outputData;

template<typename TInput>
void fillRandomData(TInput& input)
{
	using InputType = typename std::remove_reference<decltype(input[0])>::type;

	for(InputType& data : input)
	{
		data = static_cast<InputType>(std::rand());
	}
}

template<typename TInput>
void fillTestData(TInput& input)
{
	using InputType = typename std::remove_reference<decltype(input[0])>::type;

	InputType counter = InputType{};

	for(InputType& data : input)
	{
		data = counter++;
	}
}

template<typename TInput, typename TOutput>
void computeMovingAverage(TInput& input, TOutput& output, size_t frameSize)
{
	using InputType = typename std::remove_reference<decltype(input[0])>::type;
	using OutputType = typename std::remove_reference<decltype(output[0])>::type;

	size_t numFrames;
	InputType summ = 0;	
	//OutputType summ = 0;
	uint32_t i = 0;
	uint32_t n = 0;

	if(input.size() > frameSize)
	{
		numFrames = input.size() - frameSize + 1;
		numFrames = std::min(numFrames, output.size());
	}else{
		numFrames = 1;
		frameSize = input.size();
	}

	for(size_t j = 0; j < frameSize; ++j)
	{
		summ += input[j] / frameSize;
	}

	output[0] = summ;

	for(size_t i = 1; i < numFrames; ++i)
	{
		summ = summ - (input[i - 1] / frameSize) + (input[i + frameSize - 1] / frameSize);

		output[i] = summ;
	}
}

template<typename TOutput>
void dump(TOutput& output, const char *name)
{
	std::ofstream file;

	file.open(name);

	for(auto& data : output)
	{
		file << data << std::endl;
	}

	file.close();
}

int main(int argc, const char* argv[])
{
	fillTestData<Input>(inputData);

	computeMovingAverage<Input, Output>(inputData, outputData, 16);

	dump<Output>(outputData, "test.txt");


	fillRandomData<Input>(inputData);

	computeMovingAverage<Input, Output>(inputData, outputData, 16);

	dump<Output>(outputData, "random.txt");

	std::cout << "Done !" << std::endl;

	return 0;
}
