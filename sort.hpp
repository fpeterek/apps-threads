//
// Created by Filip Peterek on 03/11/2019.
//

#ifndef APPS_THREADS_SORT_HPP
#define APPS_THREADS_SORT_HPP

#include <cstdint>
#include <vector>

namespace apps {

    template<typename type>
    void sort(type * arr, const uint64_t first, const uint64_t last) {
        for (uint64_t i = first; i < last - 1; ++i) {
            for (uint64_t j = first; j < last - 1; ++j) {
                if (arr[j] > arr[j + 1]) {
                    type temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                }
            }
        }
    }

    template<typename type>
    void sort(std::vector<type> & v, const uint64_t first, const uint64_t last) {
        for (uint64_t i = first; i < last - 1; ++i) {
            for (uint64_t j = first; j < last - 1; ++j) {
                if (v[j] > v[j + 1]) {
                    type temp = v[j];
                    v[j] = v[j + 1];
                    v[j + 1] = temp;
                }
            }
        }
    }

    template<typename type>
    std::vector<type> sorted(const std::vector<type> & vector, const uint64_t first, const uint64_t last) {
        std::vector<type> v;
        uint64_t ii = 0;
        for (uint64_t i = first; i <= last; ++i) {
            v.emplace_back(vector[i]);
        }

        for (uint64_t i = 0; i < v.size() - 1; ++i) {
            for (uint64_t j = 0; j < v.size() - 1; ++j) {
                if (v[j] > v[j + 1]) {
                    type temp = v[j];
                    v[j] = v[j + 1];
                    v[j + 1] = temp;
                }
            }
        }
        return v;
    }

}

#endif //APPS_THREADS_SORT_HPP
