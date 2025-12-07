#ifndef VISUALIZER_H
#define VISUALIZER_H

#include "Process.h"
#include "PriorityQueue.h"
#include <string>
#include <vector>

class Visualizer {
public:
    // Console utilities
    static void clearScreen();
    static void printHeader(const std::string& title);
    static void printSeparator(char c = '-', int width = 60);

    // Process visualization
    static void displayProcess(const Process* process, bool detailed = false);
    static void displayProcessList(const std::vector<Process*>& processes, const std::string& title);

    // Queue visualization
    static void displayQueue(const PriorityQueue& queue, const std::string& title = "Current Queue");

    // Progress indicators
    static void displayProgressBar(int current, int total, int width = 40);
    static void displayTimeStep(int current_time, const std::string& event = "");

    // Gantt chart
    static void displayGanttChart(const std::vector<Process*>& processes);

    // Execution snapshot
    static void displayExecutionSnapshot(int current_time,
                                        const Process* running_process,
                                        const PriorityQueue& queue,
                                        int completed_count);
};

#endif // VISUALIZER_H
