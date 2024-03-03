#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <filesystem>
#include "file_search.h"
#include <string>
#include <chrono>

constexpr int TIMEOUT_SECONDS = 30; // Maximum search time (in seconds), can be changed as needed

int main() {
    std::string targetFileName;
    std::cout << "Enter the file name you want to search for: ";
    std::getline(std::cin, targetFileName);

    std::atomic<bool> stopFlag(false);
    std::atomic<int> threadsStopped(0);
    std::atomic<bool> fileFound(false);

    directoriesToSearch.push(std::filesystem::path("C:\\"));

    std::vector<std::thread> threads;
    for (int i = 0; i < MAX_THREADS; ++i) {
        threads.emplace_back([&]() {
            searchFile(targetFileName, stopFlag, threadsStopped, fileFound);
        });
    }

    std::cout << "Searching for file: " << targetFileName << std::endl;

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    bool timeoutOccurred = false;

    while (threadsStopped < MAX_THREADS && !stopFlag) {
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        if (elapsed_seconds.count() > TIMEOUT_SECONDS) {
            stopFlag = true;
            timeoutOccurred = true;
            break;
        }
    }

    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    if (timeoutOccurred && !fileFound) {
        std::cout << "File not found." << std::endl;
    }

    system("pause");
    return 0;
}