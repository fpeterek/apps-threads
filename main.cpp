#include <iostream>
#include <vector>
#include <thread>
#include <random>

#include "max.hpp"
#include "sort.hpp"
#include "merge.hpp"

typedef std::function<bool(const int64_t &, const int64_t &)> comparator;

comparator cmp(apps::lt<int64_t>);
comparator gt(apps::gt<int64_t >);

template<typename type>
std::vector<type> get_arr(size_t size) {

    std::vector<type> vector;

    std::mt19937_64 rand = std::mt19937_64(std::random_device()());
    std::uniform_int_distribution<type> dist(std::numeric_limits<type>::min(), std::numeric_limits<type>::max());

    for (size_t i = 0; i < size; ++i) {
        vector.emplace_back(dist(rand));
        //vector.emplace_back(i);
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

double time(const std::function<void(void)> & fun) {

    const auto t1 = std::chrono::high_resolution_clock::now();

    fun();

    const auto t2 = std::chrono::high_resolution_clock::now();
    const auto time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

    std::cout << "Execution time: " << time_span.count() << " seconds." << std::endl;

    return time_span.count();

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


void merge(std::vector<int64_t> & v, uint64_t threads) {

    const size_t fraction = v.size() / threads;

    std::vector<int64_t> res;
    for (uint64_t i = 0; i < fraction; ++i) {
        res.emplace_back(v[i]);
    }

    for (uint64_t i = fraction; i < v.size() - fraction + 1; i += fraction) {

        uint64_t from = i;
        uint64_t to = i + fraction - 1;
        if (v.size() - to < fraction) {
            to = v.size() - 1;
        }

        res = apps::merge(res, 0, res.size() - 1, v, from, to, cmp);

    }

    v = std::move(res);

}



void sortOnXThreads(std::vector<int64_t> v, uint64_t threads) {

    const size_t fraction = v.size() / threads;
    std::vector<std::thread> t;

    for (uint64_t i = 0; i < v.size() - fraction + 1; i += fraction) {

        uint64_t from = i;
        uint64_t to = i + fraction - 1;
        if (v.size() - to < fraction) {
            to = v.size() - 1;
        }

        t.emplace_back(
                [&](uint64_t f, uint64_t t) -> void {
                    apps::insertionSort(v, f, t, cmp);
                },
                from, to
        );

    }

    for (auto & th : t) {
        th.join();
    }

    merge(v, threads);

    if (not is_sorted(v, 0, v.size() - 1, gt)) {
        throw std::runtime_error("Vector is sorted incorrectly");
    }

}

int main() {

    constexpr size_t size = 10'000;

    std::vector<int64_t> v = get_arr<int64_t >(size);

    uint64_t threads = 1;

    double last = time( [&]() { sortOnXThreads(v, threads); } );

    while (++threads) {

        double current = time( [&]() { sortOnXThreads(v, threads); } );

        if (current >= last) {
            break;
        }

        last = current;

    }

    std::cout << "Optimal performace reached on " << threads - 1 << " threads, time: " << last << std::endl;

}
