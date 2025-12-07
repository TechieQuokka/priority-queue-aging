#include "Scheduler.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>

#ifdef _WIN32
#include <windows.h>
#endif

Scheduler::Scheduler(double aging_factor, bool verbose)
    : queue(aging_factor), current_time(0), verbose(verbose),
      visualization_delay(500) {
}

Scheduler::~Scheduler() {
    cleanup();
}

void Scheduler::cleanup() {
    for (auto* process : all_processes) {
        delete process;
    }
    all_processes.clear();
    completed_processes.clear();
}

void Scheduler::addProcess(Process* process) {
    if (process) {
        all_processes.push_back(process);
    }
}

void Scheduler::addProcess(int id, int priority, int arrival, int burst) {
    addProcess(new Process(id, priority, arrival, burst));
}

void Scheduler::generateRandomProcesses(int count, int max_priority,
                                       int max_arrival, int max_burst) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> priority_dist(1, max_priority);
    std::uniform_int_distribution<> arrival_dist(0, max_arrival);
    std::uniform_int_distribution<> burst_dist(1, max_burst);

    for (int i = 0; i < count; i++) {
        int priority = priority_dist(gen);
        int arrival = arrival_dist(gen);
        int burst = burst_dist(gen);
        addProcess(new Process(i + 1, priority, arrival, burst));
    }

    std::sort(all_processes.begin(), all_processes.end(),
              [](const Process* a, const Process* b) {
                  return a->getArrivalTime() < b->getArrivalTime();
              });
}

void Scheduler::addArrivedProcesses() {
    for (auto* process : all_processes) {
        if (process->getArrivalTime() == current_time && !process->hasStarted()) {
            queue.insert(process);
            if (verbose) {
                std::cout << "  Process " << process->getId()
                          << " arrived (Priority: " << process->getBasePriority()
                          << ", Burst: " << process->getBurstTime() << ")" << std::endl;
            }
        }
    }
}

void Scheduler::run() {
    if (all_processes.empty()) {
        std::cout << "No processes to schedule!" << std::endl;
        return;
    }

    std::sort(all_processes.begin(), all_processes.end(),
              [](const Process* a, const Process* b) {
                  return a->getArrivalTime() < b->getArrivalTime();
              });

    stats.setTotalProcesses(all_processes.size());
    current_time = 0;
    int next_arrival_idx = 0;

    if (verbose) {
        Visualizer::printHeader("SCHEDULING SIMULATION START");
        std::cout << "Aging Factor: " << queue.getAgingEvents() << std::endl;
        std::cout << "Total Processes: " << all_processes.size() << std::endl;
        Visualizer::printSeparator('-', 60);
    }

    while (next_arrival_idx < all_processes.size() || !queue.isEmpty()) {
        addArrivedProcesses();

        if (!queue.isEmpty()) {
            queue.applyAging(current_time);

            Process* current_process = queue.extractMin();

            if (current_process->getStartTime() == -1) {
                current_process->setStartTime(current_time);
            }

            if (verbose) {
                Visualizer::displayTimeStep(current_time,
                    "Executing " + current_process->toString());
                queue.display();
            }

            int execution_time = current_process->getBurstTime();
            for (int t = 0; t < execution_time; t++) {
                current_process->decrementRemainingTime();
                current_time++;
                addArrivedProcesses();
                queue.applyAging(current_time);

                if (verbose && visualization_delay > 0) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(visualization_delay));
                }
            }

            current_process->setCompletionTime(current_time);
            current_process->setWaitingTime(
                current_process->getCompletionTime() -
                current_process->getArrivalTime() -
                current_process->getBurstTime()
            );

            completed_processes.push_back(current_process);
            stats.recordProcess(current_process);

            if (verbose) {
                std::cout << "  Process " << current_process->getId()
                          << " completed at time " << current_time
                          << " (Waiting: " << current_process->getWaitingTime()
                          << ", Turnaround: " << current_process->getTurnaroundTime()
                          << ")" << std::endl;
            }
        } else {
            if (verbose) {
                Visualizer::displayTimeStep(current_time, "CPU Idle");
            }
            current_time++;
        }

        while (next_arrival_idx < all_processes.size() &&
               all_processes[next_arrival_idx]->hasStarted()) {
            next_arrival_idx++;
        }
    }

    stats.setTotalExecutionTime(current_time);
    int total_aging_events = queue.getAgingEvents();
    for (int i = 0; i < total_aging_events; i++) {
        stats.recordAgingEvent();
    }

    if (verbose) {
        Visualizer::printSeparator('=', 60);
        std::cout << "SIMULATION COMPLETED at time " << current_time << std::endl;
        Visualizer::printSeparator('=', 60);
    }
}

void Scheduler::runWithVisualization(int delay_ms) {
    setVisualizationDelay(delay_ms);
    setVerbose(true);
    run();
}

void Scheduler::displayProcessList() const {
    Visualizer::displayProcessList(all_processes, "Process List");
}

void Scheduler::displayStatistics() const {
    stats.display();
}

void Scheduler::displayGanttChart() const {
    Visualizer::displayGanttChart(completed_processes);
}
