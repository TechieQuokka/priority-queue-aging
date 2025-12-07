#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Process.h"
#include "PriorityQueue.h"
#include "Statistics.h"
#include "Visualizer.h"
#include <vector>
#include <string>

class Scheduler {
private:
    PriorityQueue queue;
    Statistics stats;
    std::vector<Process*> all_processes;
    std::vector<Process*> completed_processes;
    int current_time;
    bool verbose;               // Enable detailed output
    int visualization_delay;    // Delay in milliseconds for visualization

    // Helper methods
    void addArrivedProcesses();
    void cleanup();

public:
    // Constructor & Destructor
    Scheduler(double aging_factor = 0.1, bool verbose = true);
    ~Scheduler();

    // Process management
    void addProcess(Process* process);
    void addProcess(int id, int priority, int arrival, int burst);
    void generateRandomProcesses(int count, int max_priority = 10,
                                 int max_arrival = 20, int max_burst = 10);

    // Simulation
    void run();                 // Non-preemptive simulation
    void runWithVisualization(int delay_ms = 500);

    // Configuration
    void setVerbose(bool v) { verbose = v; }
    void setVisualizationDelay(int ms) { visualization_delay = ms; }
    void setAgingFactor(double factor) { queue.setAgingFactor(factor); }

    // Display
    void displayProcessList() const;
    void displayStatistics() const;
    void displayGanttChart() const;

    // Results
    Statistics getStatistics() const { return stats; }
    const std::vector<Process*>& getCompletedProcesses() const { return completed_processes; }
};

#endif // SCHEDULER_H
