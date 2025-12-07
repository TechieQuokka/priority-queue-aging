#include "Scheduler.h"
#include "Visualizer.h"
#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>

void runScenario1() {
    Visualizer::printHeader("SCENARIO 1: WITHOUT AGING (Starvation Demo)");
    std::cout << "\nThis scenario demonstrates starvation problem:" << std::endl;
    std::cout << "- Low priority processes may wait indefinitely" << std::endl;
    std::cout << "- High priority processes always execute first" << std::endl;
    std::cout << "\n";

    Scheduler scheduler(0.0, false);

    scheduler.addProcess(1, 1, 0, 5);
    scheduler.addProcess(2, 8, 1, 3);
    scheduler.addProcess(3, 1, 2, 4);
    scheduler.addProcess(4, 9, 3, 2);
    scheduler.addProcess(5, 1, 4, 3);

    scheduler.displayProcessList();
    scheduler.run();
    scheduler.displayGanttChart();
    scheduler.displayStatistics();

    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}

void runScenario2() {
    Visualizer::printHeader("SCENARIO 2: WITH AGING (Starvation Prevention)");
    std::cout << "\nThis scenario demonstrates aging mechanism:" << std::endl;
    std::cout << "- Priority increases based on waiting time" << std::endl;
    std::cout << "- All processes eventually get CPU time" << std::endl;
    std::cout << "- Aging Factor: 0.1" << std::endl;
    std::cout << "\n";

    Scheduler scheduler(0.1, false);

    scheduler.addProcess(1, 1, 0, 5);
    scheduler.addProcess(2, 8, 1, 3);
    scheduler.addProcess(3, 1, 2, 4);
    scheduler.addProcess(4, 9, 3, 2);
    scheduler.addProcess(5, 1, 4, 3);

    scheduler.displayProcessList();
    scheduler.run();
    scheduler.displayGanttChart();
    scheduler.displayStatistics();

    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}

void runScenario3() {
    Visualizer::printHeader("SCENARIO 3: AGGRESSIVE AGING");
    std::cout << "\nThis scenario uses aggressive aging:" << std::endl;
    std::cout << "- Aging Factor: 0.5 (vs 0.1 in Scenario 2)" << std::endl;
    std::cout << "- Faster priority boost for waiting processes" << std::endl;
    std::cout << "- More balanced execution order" << std::endl;
    std::cout << "\n";

    Scheduler scheduler(0.5, false);

    scheduler.addProcess(1, 1, 0, 5);
    scheduler.addProcess(2, 8, 1, 3);
    scheduler.addProcess(3, 1, 2, 4);
    scheduler.addProcess(4, 9, 3, 2);
    scheduler.addProcess(5, 1, 4, 3);

    scheduler.displayProcessList();
    scheduler.run();
    scheduler.displayGanttChart();
    scheduler.displayStatistics();

    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}

void runScenario4() {
    Visualizer::printHeader("SCENARIO 4: RANDOM PROCESSES (Large Scale)");
    std::cout << "\nThis scenario generates 15 random processes:" << std::endl;
    std::cout << "- Priority: 1-10 (random)" << std::endl;
    std::cout << "- Arrival Time: 0-15 (random)" << std::endl;
    std::cout << "- Burst Time: 1-8 (random)" << std::endl;
    std::cout << "- Aging Factor: 0.15" << std::endl;
    std::cout << "\n";

    Scheduler scheduler(0.15, false);
    scheduler.generateRandomProcesses(15, 10, 15, 8);

    scheduler.displayProcessList();
    scheduler.run();
    scheduler.displayGanttChart();
    scheduler.displayStatistics();

    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}

void runInteractiveDemo() {
    Visualizer::printHeader("INTERACTIVE DEMO: Real-time Visualization");
    std::cout << "\nWatch the scheduling in action with step-by-step visualization" << std::endl;
    std::cout << "Aging Factor: 0.2" << std::endl;
    std::cout << "\n";

    Scheduler scheduler(0.2, true);

    scheduler.addProcess(1, 2, 0, 4);
    scheduler.addProcess(2, 7, 1, 3);
    scheduler.addProcess(3, 3, 2, 5);
    scheduler.addProcess(4, 8, 3, 2);
    scheduler.addProcess(5, 1, 4, 4);

    scheduler.displayProcessList();
    scheduler.setVisualizationDelay(100);
    scheduler.run();
    scheduler.displayGanttChart();
    scheduler.displayStatistics();
}

void compareAgingFactors() {
    Visualizer::printHeader("COMPARISON: Different Aging Factors");

    double factors[] = {0.0, 0.05, 0.1, 0.2, 0.5};
    const char* labels[] = {"No Aging", "Conservative", "Moderate", "Aggressive", "Very Aggressive"};

    std::cout << std::left << std::setw(20) << "Aging Factor"
              << std::setw(15) << "Avg Wait"
              << std::setw(15) << "Avg Turnaround"
              << std::setw(15) << "CPU Util"
              << "Aging Events" << std::endl;
    Visualizer::printSeparator('=', 80);

    for (int i = 0; i < 5; i++) {
        Scheduler scheduler(factors[i], false);

        scheduler.addProcess(1, 1, 0, 5);
        scheduler.addProcess(2, 8, 1, 3);
        scheduler.addProcess(3, 1, 2, 4);
        scheduler.addProcess(4, 9, 3, 2);
        scheduler.addProcess(5, 1, 4, 3);

        scheduler.run();
        Statistics stats = scheduler.getStatistics();

        std::cout << std::left << std::setw(20) << labels[i]
                  << std::setw(15) << std::fixed << std::setprecision(2) << stats.getAverageWaitingTime()
                  << std::setw(15) << stats.getAverageTurnaroundTime()
                  << std::setw(15) << stats.getCpuUtilization()
                  << stats.getTotalAgingEvents() << std::endl;
    }

    Visualizer::printSeparator('=', 80);
    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}

void displayMenu() {
    Visualizer::clearScreen();
    Visualizer::printHeader("Priority Queue with Aging - Demo Program");
    std::cout << "\n";
    std::cout << "  1. Scenario 1: Without Aging (Starvation Demo)" << std::endl;
    std::cout << "  2. Scenario 2: With Aging (Starvation Prevention)" << std::endl;
    std::cout << "  3. Scenario 3: Aggressive Aging" << std::endl;
    std::cout << "  4. Scenario 4: Random Processes (Large Scale)" << std::endl;
    std::cout << "  5. Interactive Demo (Real-time Visualization)" << std::endl;
    std::cout << "  6. Compare Different Aging Factors" << std::endl;
    std::cout << "  7. Run All Scenarios" << std::endl;
    std::cout << "  0. Exit" << std::endl;
    std::cout << "\n";
    Visualizer::printSeparator('-', 60);
    std::cout << "Select option: ";
}

int main() {
    int choice;

    while (true) {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore();

        Visualizer::clearScreen();

        switch (choice) {
            case 1:
                runScenario1();
                break;
            case 2:
                runScenario2();
                break;
            case 3:
                runScenario3();
                break;
            case 4:
                runScenario4();
                break;
            case 5:
                runInteractiveDemo();
                break;
            case 6:
                compareAgingFactors();
                break;
            case 7:
                runScenario1();
                Visualizer::clearScreen();
                runScenario2();
                Visualizer::clearScreen();
                runScenario3();
                Visualizer::clearScreen();
                runScenario4();
                Visualizer::clearScreen();
                compareAgingFactors();
                break;
            case 0:
                std::cout << "\nExiting... Thank you!" << std::endl;
                return 0;
            default:
                std::cout << "\nInvalid option! Press Enter to continue...";
                std::cin.get();
        }
    }

    return 0;
}
