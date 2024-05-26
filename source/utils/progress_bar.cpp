#include "utils/progress_bar.h"
#include <string>
#include <cmath>

// ANSI color codes
#define ANSI_COLOR_RED "\033[38;5;160m"
#define ANSI_COLOR_GREEN "\033[38;5;35m"
#define ANSI_COLOR_YELLOW "\033[38;5;185m"
#define ANSI_COLOR_GREY "\033[38;5;236m"
#define ANSI_COLOR_ORANGE "\033[38;5;208m" // 256-color code for orange
#define ANSI_COLOR_RESET "\033[0m"

void ProgressBar::update(int num_steps, Population *population)
{
    std::lock_guard<std::mutex> lock(this->lock);
    if (this->current == 0)
    {
        this->start_time = std::chrono::steady_clock::now();
    }

    this->current += num_steps;

    int completedWidth = static_cast<int>(barWidth * static_cast<float>(this->current) / this->num_iterations);

    auto elapsedTime = std::chrono::steady_clock::now() - this->start_time;
    auto elapsedTimeSec = std::chrono::duration_cast<std::chrono::seconds>(elapsedTime).count();
    auto etaSec = elapsedTimeSec * (this->num_iterations - this->current) / (this->current + 1);

    int percent = static_cast<int>(std::floor(this->current * 100.0 / this->num_iterations));

    if (percent > this->last_percent_checkpoint)
    {

        std::cout.flush();

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

        std::cout << ANSI_COLOR_RED + std::to_string(this->current) + " / " + std::to_string(this->num_iterations) + " (" + std::to_string(percent) + "%)" + ANSI_COLOR_RESET;
        std::cout << ANSI_COLOR_GREY + std::string(" Metric: ") + ANSI_COLOR_RESET + ANSI_COLOR_GREEN;

        std::vector<std::vector<float>> return_objectives;
        population->find_best_fitted_individual(&return_objectives);
        for (auto met : return_objectives)
        {
            std::cout <<std::scientific << std::setprecision(3) << met[0] << " ";
        }

        std::cout << ANSI_COLOR_RESET << "\r";

        this->last_percent_checkpoint = percent;
    }
}