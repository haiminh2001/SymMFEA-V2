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

        std::cout << "\r\033[K" << ANSI_COLOR_GREY << "Elapsed: " << ANSI_COLOR_RESET << ANSI_COLOR_GREEN << formatTime(elapsedTimeSec) << ANSI_COLOR_RESET << ANSI_COLOR_GREY << " ETA: " << ANSI_COLOR_RESET << ANSI_COLOR_GREEN << formatTime(etaSec) << ANSI_COLOR_RESET;

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
        std::cout << "\n\r\033[K" << ANSI_COLOR_GREY << "Metric: " <<  ANSI_COLOR_RESET;

        std::vector<std::vector<float>> return_objectives;
        population->find_best_fitted_individual(&return_objectives);
        for (int i = 0; i < return_objectives.size(); ++i)
        {
            if (i % population->num_tasks == 0) std::cout << ANSI_COLOR_GREY << "\n\r\033[KInit "<< i / population->num_tasks<<": "<<ANSI_COLOR_RESET;
            std::cout << std::setprecision(3) << return_objectives[i][0] << " ";
        }
        // move the cursor up num inits + 2 lines
        std::cout << ANSI_COLOR_RESET << "\033["<< population->num_inits + 1 <<"A";

        this->last_percent_checkpoint = percent;

        if (percent == 100){
            std::cout << "\033["<< population->num_inits + 1 <<"B";
        }
    }
}