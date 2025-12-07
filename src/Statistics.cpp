#include "Statistics.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

Statistics::Statistics()
    : total_processes(0), completed_processes(0),
      total_waiting_time(0.0), total_turnaround_time(0.0),
      total_response_time(0.0), aging_events(0),
      max_waiting_time(0), total_burst_time(0),
      total_execution_time(0) {
}

void Statistics::recordProcess(const Process* process) {
    if (!process || !process->isCompleted()) {
        return;
    }

    completed_processes++;
    total_waiting_time += process->getWaitingTime();
    total_turnaround_time += process->getTurnaroundTime();

    if (process->getResponseTime() >= 0) {
        total_response_time += process->getResponseTime();
    }

    max_waiting_time = std::max(max_waiting_time, process->getWaitingTime());
    total_burst_time += process->getBurstTime();
}

void Statistics::recordAgingEvent(int process_id) {
    aging_events++;
    if (process_id >= 0) {
        priority_changes[process_id]++;
    }
}

double Statistics::getAverageWaitingTime() const {
    if (completed_processes == 0) return 0.0;
    return total_waiting_time / completed_processes;
}

double Statistics::getAverageTurnaroundTime() const {
    if (completed_processes == 0) return 0.0;
    return total_turnaround_time / completed_processes;
}

double Statistics::getAverageResponseTime() const {
    if (completed_processes == 0) return 0.0;
    return total_response_time / completed_processes;
}

double Statistics::getCpuUtilization() const {
    if (total_execution_time == 0) return 0.0;
    return (static_cast<double>(total_burst_time) / total_execution_time) * 100.0;
}

void Statistics::reset() {
    total_processes = 0;
    completed_processes = 0;
    total_waiting_time = 0.0;
    total_turnaround_time = 0.0;
    total_response_time = 0.0;
    aging_events = 0;
    max_waiting_time = 0;
    total_burst_time = 0;
    total_execution_time = 0;
    priority_changes.clear();
}

void Statistics::display() const {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "                    STATISTICS REPORT" << std::endl;
    std::cout << std::string(60, '=') << std::endl;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "  Total Processes:          " << total_processes << std::endl;
    std::cout << "  Completed Processes:      " << completed_processes << std::endl;
    std::cout << "  Total Execution Time:     " << total_execution_time << " time units" << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    std::cout << "  Average Waiting Time:     " << getAverageWaitingTime() << " time units" << std::endl;
    std::cout << "  Average Turnaround Time:  " << getAverageTurnaroundTime() << " time units" << std::endl;
    std::cout << "  Average Response Time:    " << getAverageResponseTime() << " time units" << std::endl;
    std::cout << "  Maximum Waiting Time:     " << max_waiting_time << " time units" << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    std::cout << "  CPU Utilization:          " << getCpuUtilization() << "%" << std::endl;
    std::cout << "  Total Aging Events:       " << aging_events << std::endl;

    if (!priority_changes.empty()) {
        std::cout << "  Processes with Priority Changes: " << priority_changes.size() << std::endl;
    }

    std::cout << std::string(60, '=') << std::endl;
}

std::string Statistics::generateReport() const {
    std::ostringstream oss;

    oss << std::fixed << std::setprecision(2);
    oss << "Statistics: ";
    oss << "Avg Wait=" << getAverageWaitingTime() << ", ";
    oss << "Avg Turnaround=" << getAverageTurnaroundTime() << ", ";
    oss << "CPU=" << getCpuUtilization() << "%, ";
    oss << "Aging Events=" << aging_events;

    return oss.str();
}
