#include <iostream>
#include <vector>
#include <thread>
#include <random>

#include "max.hpp"
#include "sort.hpp"
#include "merge.hpp"

template<typename type>
std::vector<type> get_arr(size_t size) {

    std::vector<type> vector;

    std::mt19937_64 rand = std::mt19937_64(std::random_device()());
    std::uniform_int_distribution<type> dist(std::numeric_limits<type>::min(), std::numeric_limits<type>::max());

    for (size_t i = 0; i < size; ++i) {
        vector.emplace_back(i);
    }

    return vector;

}

template<typename type>
void print_vector(std::ostream & os, const std::vector<type> & v, const size_t first, const size_t last) {

    for (size_t i = first; i <= last; ++i) {
        os << v[i] << std::endl;
    }

}

template<typename type>
std::ostream & operator<<(std::ostream & os, const std::vector<type> & v) {
    for (const type & t : v) {
        os << t << std::endl;
    }
    return os;
}

template<typename type>
bool is_sorted(const std::vector<type> & v, const size_t first, const size_t last, std::function<bool(const type &, const type &)> cmp) {

    for (size_t i = first; i < last; ++i) {
        if (not cmp(v[i], v[i + 1])) {
            return false;
        }
    }

    return true;

}

void time(const std::function<void(void)> & fun) {

    const auto t1 = std::chrono::high_resolution_clock::now();

    fun();

    const auto t2 = std::chrono::high_resolution_clock::now();
    const auto time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

    std::cout << "Execution time: " << time_span.count() << " seconds." << std::endl;

}

template<typename type>
void one_thread(const size_t size, const bool printVector = false) {

    std::function<bool(const uint64_t &, const uint64_t &)> cmp(apps::lt<uint64_t>);

    auto vector = get_arr<type>(size);

    std::cout << "Sorting on one thread" << std::endl;

    auto sort = [&]() -> void { apps::insertionSort(vector, 0, vector.size() - 1, cmp); };

    time([&]() -> void { std::thread t(sort); t.join(); std::cout << "Sorted" << std::endl; });

    std::cout << "Checking if vector is sorted: " << is_sorted(vector, 0, vector.size() - 1, cmp) << std::endl;

    if (printVector) {
        std::cout << vector << std::endl;
    }

}

template<typename type>
void two_threads(const size_t size, const bool printVector = false) {

    std::function<bool(const uint64_t &, const uint64_t &)> cmp(apps::lt<uint64_t>);

    auto vector = get_arr<type>(size);

    std::cout << "Sorting on two threads" << std::endl;

    const size_t middle = vector.size() / 2;

    auto sortL = [&]() -> void { apps::insertionSort(vector, 0, middle, cmp); };
    auto sortR = [&]() -> void { apps::insertionSort(vector, middle + 1, vector.size() - 1, cmp); };

    auto sort = [&]() -> void {
        std::thread t(sortL);
        std::thread t2(sortR);
        t.join();
        t2.join();
        std::cout << "Sorted" << std::endl;

    };

    time(sort);

    auto merged = apps::merge(vector, 0, middle, vector, middle + 1, vector.size() - 1, cmp);

    std::cout << "Checking if vector is sorted: " << is_sorted(merged, 0, merged.size() - 1, cmp) << std::endl;

    if (printVector) {
        std::cout << merged << std::endl;
    }

}

template<typename type>
void four_threads(const size_t size, const bool printVector = false) {

    std::function<bool(const uint64_t &, const uint64_t &)> cmp(apps::gt<uint64_t>);

    auto vector = get_arr<type>(size);

    std::cout << "Sorting on four threads" << std::endl;

    const size_t left = vector.size() / 4;
    const size_t middle = vector.size() / 4 * 2;
    const size_t right = vector.size() / 4 * 3;

    auto sortLL = [&]() -> void { apps::insertionSort(vector, 0, left, cmp); };
    auto sortML = [&]() -> void { apps::insertionSort(vector, left + 1, middle, cmp); };
    auto sortLR = [&]() -> void { apps::insertionSort(vector, middle + 1, right, cmp); };
    auto sortRR = [&]() -> void { apps::insertionSort(vector, right + 1, vector.size() - 1, cmp); };

    auto sort = [&]() -> void {
        std::thread t1(sortLL);
        std::thread t2(sortML);
        std::thread t3(sortLR);
        std::thread t4(sortRR);

        t1.join();
        t2.join();
        t3.join();
        t4.join();
        std::cout << "Sorted" << std::endl;

    };

    time(sort);

    auto mergedLeft = apps::merge(vector, 0, left, vector, left + 1, middle, cmp);
    auto mergedRight = apps::merge(vector, middle + 1, right, vector, right + 1, vector.size() - 1, cmp);

    auto merged = apps::merge(mergedLeft, 0, mergedLeft.size() - 1, mergedRight, 0, mergedRight.size() - 1, cmp);

    std::cout << "Checking if vector is sorted: " << is_sorted(merged, 0, merged.size() - 1, cmp) << std::endl;

    if (printVector) {
        std::cout << merged << std::endl;
    }

}

int main() {

    constexpr size_t size = 1'000'000;


    std::vector<uint64_t> v1 = {1, 3, 5, 2, 4, 6};
    std::vector<uint64_t> dest;
    dest.reserve(v1.size());

    std::function<bool(const uint64_t &, const uint64_t &)> cmp(apps::gt<uint64_t>);

    apps::mergeInto(v1, 0, 2, v1, 3, 5, dest, 0, cmp);
    for (uint64_t i : dest) {
        std::cout << i << " ";
    }
    std::endl(std::cout);

    auto dest2 = apps::merge(v1, 0, 2, v1, 3, 5, cmp);
    for (uint64_t i : dest2) {
        std::cout << i << " ";
    }
    std::endl(std::cout);


    //one_thread<uint64_t>(size);
    //two_threads<uint64_t>(size);
    //four_threads<uint64_t>(size);

    constexpr size_t s2 = 5;
    four_threads<uint64_t>(s2, true);

}
