#include "utils/progress_bar.h"
#include <string>

ProgressBar::ProgressBar(int num_iterations, int barWidth)
{
    this->num_iterations = num_iterations;
    this->current = 0;
    this->barWidth = barWidth;
}

void ProgressBar::updateProgress(int num_steps, std::vector<Individual *> best_individuals)
{

    if (this->current == 0)
    {
        this->start_time = std::chrono::steady_clock::now();
    }

    this->current += num_steps;

    int completedWidth = static_cast<int>(barWidth * static_cast<float>(this->current) / this->num_iterations);

    auto elapsedTime = std::chrono::steady_clock::now() - this->start_time;
    auto elapsedTimeSec = std::chrono::duration_cast<std::chrono::seconds>(elapsedTime).count();
    auto etaSec = elapsedTimeSec * (this->num_iterations - this->current) / (this->current + 1);

    std::cout << "Elapsed: " << formatTime(elapsedTimeSec) << " ETA: " << formatTime(etaSec);

    std::cout << "[";
    for (int i = 0; i < barWidth; ++i)
    {
        if (i < completedWidth)
        {
            std::cout << "=";
        }
        else if (i == completedWidth)
        {
            std::cout << ">";
        }
        else
        {
            std::cout << " ";
        }
    }

    std::string metrics = "";

    for (auto ind : best_individuals)
    {
        auto met = ind->objectives()(0);
        metrics += std::to_string(met);
        metrics += " ";
    }

    std::cout << "] " << std::setw(3);

    std::cout << "Current Generation: " << this->current << " / " << this->num_iterations << " (" << static_cast<int>(this->current * 100.0 / this->num_iterations) << "%) ";
    std::cout << "Metric: " << metrics;

    std::cout << "\r";
    std::cout.flush();
}