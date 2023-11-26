#include "utils/progress_bar.h"
#include <string>

// ANSI color codes
#define ANSI_COLOR_RED "\033[38;5;160m"
#define ANSI_COLOR_GREEN "\033[38;5;35m"
#define ANSI_COLOR_YELLOW "\033[38;5;185m"
#define ANSI_COLOR_GREY "\033[38;5;236m"
#define ANSI_COLOR_ORANGE "\033[38;5;208m" // 256-color code for orange
#define ANSI_COLOR_RESET "\033[0m"

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

    std::cout << ANSI_COLOR_GREY << "Elapsed: " << ANSI_COLOR_RESET << ANSI_COLOR_GREEN << formatTime(elapsedTimeSec) << ANSI_COLOR_RESET << ANSI_COLOR_GREY << " ETA: " << ANSI_COLOR_RESET << ANSI_COLOR_GREEN << formatTime(etaSec) << ANSI_COLOR_RESET;

    std::cout << ANSI_COLOR_ORANGE << " [" << ANSI_COLOR_RESET << ANSI_COLOR_YELLOW;

    // Print completed part of the progress bar in orange
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

    std::cout << ANSI_COLOR_RESET << ANSI_COLOR_ORANGE << "]; " << std::setw(3) << ANSI_COLOR_RESET;

    std::string metrics = "";

    for (auto ind : best_individuals)
    {
        auto met = ind->objectives()(0);
        metrics += std::to_string(met);
        metrics += " ";
    }

    // Print current generation in grey
    std::cout << ANSI_COLOR_GREY << "Current Generation: " << ANSI_COLOR_RESET << ANSI_COLOR_RED << this->current << " / " << this->num_iterations << " (" << static_cast<int>(this->current * 100.0 / this->num_iterations) << "%)" << ANSI_COLOR_RESET;
    // Print metric in green
    std::cout << ANSI_COLOR_GREY << " Metric: " << ANSI_COLOR_RESET << ANSI_COLOR_GREEN << metrics << ANSI_COLOR_RESET;

    std::cout << "\r";
    std::cout.flush();
}