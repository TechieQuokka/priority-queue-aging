#include "Visualizer.h"
#include <iostream>
#include <iomanip>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

void Visualizer::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Visualizer::printHeader(const std::string& title) {
    printSeparator('=', 60);
    std::cout << "  " << title << std::endl;
    printSeparator('=', 60);
}

void Visualizer::printSeparator(char c, int width) {
    std::cout << std::string(width, c) << std::endl;
}

void Visualizer::displayProcess(const Process* process, bool detailed) {
    if (!process) {
        std::cout << "  [NULL Process]" << std::endl;
        return;
    }

    if (detailed) {
        std::cout << "  " << process->toDetailedString() << std::endl;
    } else {
        std::cout << "  " << process->toString() << std::endl;
    }
}

void Visualizer::displayProcessList(const std::vector<Process*>& processes, const std::string& title) {
    std::cout << "\n" << title << " (" << processes.size() << " processes):" << std::endl;
    printSeparator('-', 60);

    if (processes.empty()) {
        std::cout << "  [No processes]" << std::endl;
        return;
    }

    for (const auto* process : processes) {
        displayProcess(process, true);
    }
    printSeparator('-', 60);
}

void Visualizer::displayQueue(const PriorityQueue& queue, const std::string& title) {
    std::cout << "\n" << title << ":" << std::endl;
    printSeparator('-', 60);
    queue.display();
    printSeparator('-', 60);
}

void Visualizer::displayProgressBar(int current, int total, int width) {
    if (total == 0) return;

    float progress = static_cast<float>(current) / total;
    int pos = static_cast<int>(width * progress);

    std::cout << "  [";
    for (int i = 0; i < width; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << "%\r";
    std::cout.flush();
}

void Visualizer::displayTimeStep(int current_time, const std::string& event) {
    std::cout << "\n[Time " << std::setw(3) << current_time << "] ";
    if (!event.empty()) {
        std::cout << event;
    }
    std::cout << std::endl;
}

void Visualizer::displayGanttChart(const std::vector<Process*>& processes) {
    if (processes.empty()) {
        return;
    }

    std::cout << "\nGantt Chart:" << std::endl;
    printSeparator('-', 60);

    int max_time = 0;
    for (const auto* process : processes) {
        if (process->getCompletionTime() > max_time) {
            max_time = process->getCompletionTime();
        }
    }

    for (const auto* process : processes) {
        if (!process->hasStarted()) continue;

        std::cout << "  P" << std::setw(2) << std::setfill('0') << process->getId()
                  << " |";

        for (int t = 0; t < max_time; t++) {
            if (t >= process->getStartTime() && t < process->getCompletionTime()) {
                std::cout << "=";
            } else {
                std::cout << " ";
            }
        }
        std::cout << "| (" << process->getStartTime()
                  << "-" << process->getCompletionTime() << ")" << std::endl;
    }

    std::cout << "     0";
    for (int t = 5; t <= max_time; t += 5) {
        std::cout << std::setw(5) << t;
    }
    std::cout << std::endl;
    printSeparator('-', 60);
}

void Visualizer::displayExecutionSnapshot(int current_time,
                                         const Process* running_process,
                                         const PriorityQueue& queue,
                                         int completed_count) {
    std::cout << "\n" << std::string(60, '-') << std::endl;
    std::cout << "[Time: " << current_time << "] ";

    if (running_process) {
        std::cout << "Running: " << running_process->toString()
                  << " (Remaining: " << running_process->getRemainingTime() << ")"
                  << std::endl;
    } else {
        std::cout << "CPU Idle" << std::endl;
    }

    std::cout << "Completed: " << completed_count << " | Queue Size: " << queue.size() << std::endl;

    if (!queue.isEmpty()) {
        std::cout << "Queue: ";
        queue.display();
    }
}
