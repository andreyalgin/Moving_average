#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <array>

#include <unistd.h>

using Input = std::array<int, 64>;
using Output = std::array<int, 49>;

static Input inputData;
static Output outputData;

template<typename TInput>
void randomizeData(TInput input)
{
	using DataType = decltype(+input[0]);

	for(DataType& data : input)
	{
		data = static_cast<DataType>(std::rand());
	}
}

template<typename TInput, typename TOutput>
void computeMovingAverage(TInput input, TOutput output, uint32_t frameSize)
{

}

int main(int argc, const char* argv[])
{
	std::cout << "Hello" << std::endl;

	randomizeData<Input>(inputData);

	computeMovingAverage<Input, Output>(inputData, outputData, 16);

	return 0;
}

