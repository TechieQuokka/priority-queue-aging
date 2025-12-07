#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "Process.h"
#include <vector>

class PriorityQueue {
private:
    std::vector<Process*> heap;     // Min-heap array (lower priority value = higher priority)
    double aging_factor;            // Aging rate (default 0.1)
    int current_time;               // Simulation time
    int aging_events;               // Count of priority adjustments

    // Heap helper methods
    int parent(int i) const { return (i - 1) / 2; }
    int leftChild(int i) const { return 2 * i + 1; }
    int rightChild(int i) const { return 2 * i + 2; }

    // Heap operations
    void heapifyUp(int index);
    void heapifyDown(int index);
    void swap(int i, int j);

    // Comparison based on effective priority
    bool hasHigherPriority(int i, int j) const;

public:
    // Constructor & Destructor
    PriorityQueue(double aging_factor = 0.1);
    ~PriorityQueue();

    // Core operations
    void insert(Process* process);
    Process* extractMin();          // Get highest priority (lowest value)
    Process* peek() const;

    // Aging mechanism
    void applyAging(int current_time);
    void updateAllPriorities(int current_time);
    void rebuildHeap();

    // Queue state
    bool isEmpty() const { return heap.empty(); }
    int size() const { return heap.size(); }

    // Statistics
    int getAgingEvents() const { return aging_events; }
    void resetAgingEvents() { aging_events = 0; }

    // Setters
    void setCurrentTime(int time) { current_time = time; }
    void setAgingFactor(double factor) { aging_factor = factor; }

    // Visualization
    std::vector<Process*> getQueueSnapshot() const;
    void display() const;
    void displayDetailed() const;
};

#endif // PRIORITY_QUEUE_H
