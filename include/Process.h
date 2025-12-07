#ifndef PROCESS_H
#define PROCESS_H

#include <string>

class Process {
private:
    int id;                      // Unique identifier
    int base_priority;           // Original priority (1-10, lower is higher)
    int arrival_time;            // When process arrives
    int burst_time;              // Execution time needed
    int remaining_time;          // Remaining execution time
    int waiting_time;            // Time spent waiting
    int start_time;              // When execution started (-1 if not started)
    int completion_time;         // When finished (-1 if not finished)
    double effective_priority;   // Current priority after aging

public:
    // Constructor
    Process(int id, int priority, int arrival, int burst);

    // Getters
    int getId() const { return id; }
    int getBasePriority() const { return base_priority; }
    double getEffectivePriority() const { return effective_priority; }
    int getArrivalTime() const { return arrival_time; }
    int getBurstTime() const { return burst_time; }
    int getRemainingTime() const { return remaining_time; }
    int getWaitingTime() const { return waiting_time; }
    int getStartTime() const { return start_time; }
    int getCompletionTime() const { return completion_time; }

    // Setters
    void setStartTime(int time) { start_time = time; }
    void setCompletionTime(int time) { completion_time = time; }
    void setWaitingTime(int time) { waiting_time = time; }
    void decrementRemainingTime() { if (remaining_time > 0) remaining_time--; }

    // Priority calculation
    void updateEffectivePriority(int current_time, double aging_factor);

    // Time calculations
    int getTurnaroundTime() const;
    int getResponseTime() const;

    // Display
    std::string toString() const;
    std::string toDetailedString() const;

    // Status check
    bool isCompleted() const { return remaining_time == 0; }
    bool hasStarted() const { return start_time != -1; }
};

#endif // PROCESS_H
