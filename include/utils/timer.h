#ifndef SYMMFEA_TIMER_H
#define SYMMFEA_TIMER_H
#include <chrono>
#include <map>
#include <utility>
#include <iostream>

typedef std::chrono::high_resolution_clock::time_point TimeVar;

#define duration(a) std::chrono::duration_cast<std::chrono::microseconds>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()

namespace Timer
{
    std::map<std::string, int64_t> timeMap;

    std::chrono::high_resolution_clock::time_point tmp_start_time;

    void startTimer()
    {
        tmp_start_time = timeNow();
    }

    void logTime(std::string key)
    {
        if (timeMap.find(key) == timeMap.end())
        {
            timeMap.insert(std::pair<std::string, int64_t>(key, 0));
        }
        timeMap[key] += duration(timeNow() - tmp_start_time);
    }

    void printTime()
    {
        std::cout<<std::endl;
        for (auto &it : timeMap)
        {
            std::cout << it.first << " : " << double(it.second) * 1e-6 << " s" << std::endl;
        }
    }
}

#endif // SYMMFEA_TIMER_H
