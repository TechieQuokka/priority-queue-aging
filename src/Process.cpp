#include "Process.h"
#include <sstream>
#include <iomanip>
#include <algorithm>

Process::Process(int id, int priority, int arrival, int burst)
    : id(id), base_priority(priority), arrival_time(arrival),
      burst_time(burst), remaining_time(burst), waiting_time(0),
      start_time(-1), completion_time(-1), effective_priority(priority) {
}

void Process::updateEffectivePriority(int current_time, double aging_factor) {
    if (completion_time != -1) {
        return;
    }

    int time_waited = current_time - arrival_time;
    if (start_time != -1) {
        time_waited -= (current_time - start_time);
    }

    waiting_time = std::max(0, time_waited);

    effective_priority = base_priority - (waiting_time * aging_factor);
    effective_priority = std::max(0.0, effective_priority);
}

int Process::getTurnaroundTime() const {
    if (completion_time == -1) {
        return -1;
    }
    return completion_time - arrival_time;
}

int Process::getResponseTime() const {
    if (start_time == -1) {
        return -1;
    }
    return start_time - arrival_time;
}

std::string Process::toString() const {
    std::ostringstream oss;
    oss << "P" << std::setw(2) << std::setfill('0') << id
        << " [Pri:" << std::setw(4) << std::fixed << std::setprecision(1)
        << effective_priority << "/" << base_priority << "]";
    return oss.str();
}

std::string Process::toDetailedString() const {
    std::ostringstream oss;
    oss << "Process " << std::setw(2) << std::setfill('0') << id << ": "
        << "Base Priority=" << base_priority
        << ", Effective Priority=" << std::fixed << std::setprecision(2) << effective_priority
        << ", Arrival=" << arrival_time
        << ", Burst=" << burst_time
        << ", Remaining=" << remaining_time
        << ", Waiting=" << waiting_time;

    if (start_time != -1) {
        oss << ", Start=" << start_time;
    }
    if (completion_time != -1) {
        oss << ", Completion=" << completion_time
            << ", Turnaround=" << getTurnaroundTime();
    }

    return oss.str();
}
