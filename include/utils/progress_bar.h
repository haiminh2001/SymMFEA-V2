#ifndef SYMMFEA_PROGRESS_BAR_H
#define SYMMFEA_PROGRESS_BAR_H

#include <iostream>
#include <chrono>
#include <iomanip>
#include <evolution/population/individual.h>

class ProgressBar
{
private:
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
    ProgressBar(int num_iterations, int bar_width = 70);
    void updateProgress(int num_steps, std::vector <Individual*> best_individuals);
};


#endif // SYMMFEA_PROGRESS_BAR_H
