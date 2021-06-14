class Timer {
public:
    Timer() {
        start = std::chrono::high_resolution_clock::now();
    }

    ~Timer() {
        finish = std::chrono::high_resolution_clock::now();
        std::cout << "Time elapsed: " << std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count() / 1000.0f) << " ms\n";
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::chrono::time_point<std::chrono::high_resolution_clock> finish;
};