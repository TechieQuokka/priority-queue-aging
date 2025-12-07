#include "PriorityQueue.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

PriorityQueue::PriorityQueue(double aging_factor)
    : aging_factor(aging_factor), current_time(0), aging_events(0) {
}

PriorityQueue::~PriorityQueue() {
}

bool PriorityQueue::hasHigherPriority(int i, int j) const {
    if (i >= heap.size() || j >= heap.size()) {
        return false;
    }
    return heap[i]->getEffectivePriority() < heap[j]->getEffectivePriority();
}

void PriorityQueue::swap(int i, int j) {
    if (i < heap.size() && j < heap.size()) {
        std::swap(heap[i], heap[j]);
    }
}

void PriorityQueue::heapifyUp(int index) {
    while (index > 0 && hasHigherPriority(index, parent(index))) {
        swap(index, parent(index));
        index = parent(index);
    }
}

void PriorityQueue::heapifyDown(int index) {
    int smallest = index;
    int left = leftChild(index);
    int right = rightChild(index);

    if (left < heap.size() && hasHigherPriority(left, smallest)) {
        smallest = left;
    }

    if (right < heap.size() && hasHigherPriority(right, smallest)) {
        smallest = right;
    }

    if (smallest != index) {
        swap(index, smallest);
        heapifyDown(smallest);
    }
}

void PriorityQueue::insert(Process* process) {
    if (!process) return;

    process->updateEffectivePriority(current_time, aging_factor);
    heap.push_back(process);
    heapifyUp(heap.size() - 1);
}

Process* PriorityQueue::extractMin() {
    if (isEmpty()) {
        return nullptr;
    }

    Process* minProcess = heap[0];

    heap[0] = heap.back();
    heap.pop_back();

    if (!isEmpty()) {
        heapifyDown(0);
    }

    return minProcess;
}

Process* PriorityQueue::peek() const {
    if (isEmpty()) {
        return nullptr;
    }
    return heap[0];
}

void PriorityQueue::updateAllPriorities(int current_time) {
    this->current_time = current_time;

    for (Process* process : heap) {
        double old_priority = process->getEffectivePriority();
        process->updateEffectivePriority(current_time, aging_factor);
        double new_priority = process->getEffectivePriority();

        if (std::abs(new_priority - old_priority) > 0.01) {
            aging_events++;
        }
    }
}

void PriorityQueue::applyAging(int current_time) {
    updateAllPriorities(current_time);
    rebuildHeap();
}

void PriorityQueue::rebuildHeap() {
    for (int i = heap.size() / 2 - 1; i >= 0; i--) {
        heapifyDown(i);
    }
}

std::vector<Process*> PriorityQueue::getQueueSnapshot() const {
    return heap;
}

void PriorityQueue::display() const {
    if (isEmpty()) {
        std::cout << "  [Queue is empty]" << std::endl;
        return;
    }

    std::cout << "  Queue (" << size() << " processes): ";
    for (size_t i = 0; i < heap.size(); i++) {
        std::cout << heap[i]->toString();
        if (i < heap.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

void PriorityQueue::displayDetailed() const {
    if (isEmpty()) {
        std::cout << "  [Queue is empty]" << std::endl;
        return;
    }

    std::cout << "  Queue (" << size() << " processes):" << std::endl;
    for (size_t i = 0; i < heap.size(); i++) {
        std::cout << "    [" << i << "] " << heap[i]->toDetailedString() << std::endl;
    }
}
