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

namespace profiler
{
    struct Item
    {
        uint32_t counter;
        const char *name;
        clock_t timeSpent;
    };

    class Profiler
    {
    public:
        Profiler(const char *name)
        {
            m_name = name;
            m_begin = clock();
        }

        ~Profiler()
        {
            clock_t end = clock();
            clock_t timeSpent = end - m_begin;

            m_items[m_counter].counter = m_counter;
            m_items[m_counter].name = m_name;
            m_items[m_counter].timeSpent = timeSpent;

            m_counter++;
        }

        static void dump(const char *name)
        {
            std::ofstream file;

            file.open(name);

            for(auto& item : m_items)
            {
                file << item.counter << " " << item.name << " " << item.timeSpent << std::endl;
            }

            file.close();
        }

    private:
        static std::array<Item, 16> m_items;
        static uint32_t m_counter;

        const char *m_name;
        clock_t m_begin;
    };

    std::array<Item, 16> Profiler::m_items;
    uint32_t Profiler::m_counter = 0;    
}
