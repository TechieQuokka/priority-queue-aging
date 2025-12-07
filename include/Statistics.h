#ifndef STATISTICS_H
#define STATISTICS_H

#include "Process.h"
#include <vector>
#include <map>
#include <string>

class Statistics {
private:
    int total_processes;
    int completed_processes;
    double total_waiting_time;
    double total_turnaround_time;
    double total_response_time;
    int aging_events;
    int max_waiting_time;
    int total_burst_time;
    int total_execution_time;
    std::map<int, int> priority_changes;  // Track changes per process

public:
    Statistics();

    // Recording
    void recordProcess(const Process* process);
    void recordAgingEvent(int process_id = -1);
    void setTotalProcesses(int count) { total_processes = count; }
    void setTotalExecutionTime(int time) { total_execution_time = time; }

    // Calculations
    double getAverageWaitingTime() const;
    double getAverageTurnaroundTime() const;
    double getAverageResponseTime() const;
    double getCpuUtilization() const;
    int getTotalAgingEvents() const { return aging_events; }
    int getMaxWaitingTime() const { return max_waiting_time; }
    int getCompletedProcesses() const { return completed_processes; }

    // Reset
    void reset();

    // Display
    void display() const;
    std::string generateReport() const;
};

#endif // STATISTICS_H
