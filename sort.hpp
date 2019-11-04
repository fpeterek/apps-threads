//
// Created by Filip Peterek on 03/11/2019.
//

#ifndef APPS_THREADS_SORT_HPP
#define APPS_THREADS_SORT_HPP

#include <cstdint>
#include <vector>

namespace apps {

    template<typename type>
    void selectionSort(type * arr, const uint64_t first, const uint64_t last) {

        for (uint64_t i = first; i < last; ++i) {

            uint64_t min = i;

            for (uint64_t j = i; j <= last; ++j) {
                arr[min] > arr[j] and min = j;
            }

            type temp = arr[min];
            arr[min] = arr[i];
            arr[i] = temp;

        }

    }

    template<typename type>
    void selectionSort(std::vector<type> v, const uint64_t first, const uint64_t last) {

        for (uint64_t i = first; i < last; ++i) {

            uint64_t min = i;

            for (uint64_t j = i; j <= last; ++j) {
                v[min] > v[j] and min = j;
            }

            type temp = v[min];
            v[min] = v[i];
            v[i] = temp;

        }

    }

    template<typename type>
    void insertionSort(type * arr, const uint64_t first, const uint64_t last) {

        for (uint64_t i = first + 1; i <= last; ++i) {

            type temp = arr[i];
            uint64_t j;

            for (j = i; j > first and arr[j - 1] > temp ; --j) {
                arr[j] = arr[j - 1];
            }

            arr[j] = temp;

        }

    }

    template<typename type>
    void insertionSort(std::vector<type> & v, const uint64_t first, const uint64_t last) {

        for (uint64_t i = first + 1; i <= last; ++i) {

            type temp = v[i];
            uint64_t j;

            for (j = i; j > first and v[j - 1] > temp ; --j) {
                v[j] = v[j - 1];
            }

            v[j] = temp;

        }

    }

    template<typename type>
    void bubbleSort(type * arr, const uint64_t first, const uint64_t last) {
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
    void bubbleSort(std::vector<type> & v, const uint64_t first, const uint64_t last) {
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
        for (uint64_t i = first; i <= last; ++i) {
            v.emplace_back(vector[i]);
        }

        bubbleSort(v, 0, v.size() - 1);
        return v;
    }

}

#endif //APPS_THREADS_SORT_HPP
