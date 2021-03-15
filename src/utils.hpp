#include <iomanip>
#include <iostream>
#include <random>
#include <string>

namespace utility {
    template<typename T=int>
    T random_int(T low, T high) {
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution dist(low, high); // define the range
        return dist(gen);
    }

    template<typename Func, typename... Args>
    void timeit(const std::string& description, Func&& f, Args&&... args) {
        auto start = std::chrono::steady_clock::now();
        f(std::forward<Args>(args)...);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = end - start;
        std::cout << std::fixed << std::setprecision(5) << std::left;
        std::cout << description << diff.count() << "s\n";
    }

    template<typename T, typename Func, typename... Args>
    void timeit(const std::string& description, T* obj, Func&& f, Args&&... args) {
        auto start = std::chrono::steady_clock::now();
        (obj->*f)(std::forward<Args>(args)...);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = end - start;
        std::cout << std::fixed << std::setprecision(5) << std::left;
        std::cout << description << diff.count() << "s\n";
    }
}