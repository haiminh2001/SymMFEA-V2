#ifndef SYMMFEA_PROGRESS_BAR_H
#define SYMMFEA_PROGRESS_BAR_H


#include "evolution/population/population.h"

#include <iostream>
#include <chrono>
#include <iomanip>
#include <mutex>



class ProgressBar
{
private:
    std::mutex lock;
    std::string last_metric_string;
    int last_percent_checkpoint;
    int num_iterations;
    int current;
    int barWidth;
    std::chrono::time_point<std::chrono::steady_clock> start_time;
    std::string formatTime(int seconds)
    {
        int hours = seconds / 3600;
        int minutes = (seconds % 3600) / 60;
        seconds = seconds % 60;

        std::ostringstream oss;
        oss << std::setfill('0') << std::setw(2) << hours << ":";
        oss << std::setfill('0') << std::setw(2) << minutes << ":";
        oss << std::setfill('0') << std::setw(2) << seconds;

        return oss.str();
    }

public:
    ProgressBar(int num_iterations, int barWidth)
        : last_percent_checkpoint(-1),
          num_iterations(num_iterations),
          current(0),
          barWidth(barWidth),
          last_metric_string("") {}
    void update(int num_steps, Population *population);
};

#endif // SYMMFEA_PROGRESS_BAR_H
