#include "file_search.h"
#include <condition_variable>

std::mutex mtx;
std::queue<std::filesystem::path> directoriesToSearch;
std::condition_variable cv;

void searchFile(const std::string& target, std::atomic<bool>& stopFlag, std::atomic<int>& threadsStopped, std::atomic<bool>& fileFound) {
    while (!stopFlag) {
        std::filesystem::path currentPath;

        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [&]() { return !directoriesToSearch.empty() || stopFlag; });

            if (directoriesToSearch.empty() && stopFlag) {
                break;
            }

            if (!directoriesToSearch.empty()) {
                currentPath = directoriesToSearch.front();
                directoriesToSearch.pop();
            }
        }

        if (currentPath.has_root_name() && currentPath.root_name() != "C:") {
            continue;
        }

        try {
            for (const auto& entry : std::filesystem::directory_iterator(currentPath)) {
                if (stopFlag) return;

                if (entry.is_directory()) {
                    std::lock_guard<std::mutex> lock(mtx);
                    directoriesToSearch.push(entry.path());
                    cv.notify_one();
                } else if (entry.is_regular_file() && entry.path().filename() == target) {
                    std::string filePath = entry.path().string();
                    {
                        std::lock_guard<std::mutex> lock(mtx);
                        if (!fileFound.exchange(true)) {
                            std::cout << "File found: " << filePath << std::endl;
                            stopFlag = true;
                            threadsStopped++;
                            return;
                        }
                    }
                }
            }
        } catch (const std::exception& ex) {
        }
    }

    threadsStopped++;
}