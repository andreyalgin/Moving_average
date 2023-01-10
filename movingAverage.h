#pragma once

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

namespace movingAverage
{
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
        OutputType summ = OutputType{};

        if(input.size() > frameSize)
        {
            numFrames = input.size() - frameSize + 1;
            numFrames = std::min(numFrames, output.size());
        }else{
            numFrames = 1;
            frameSize = input.size();
        }

        std::cout << "Frame size: " << frameSize << std::endl;

        for(size_t j = 0; j < frameSize; ++j)
        {
            summ += input[j] / frameSize;
        }

        output[0] = summ;

        for(size_t i = 1; i < numFrames; ++i)
        {
            summ -= static_cast<OutputType>(input[i - 1]) / static_cast<OutputType>(frameSize);
            summ += static_cast<OutputType>(input[i + frameSize - 1]) / static_cast<OutputType>(frameSize);

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
}
