//
// Created by Filip Peterek on 03/11/2019.
//

#ifndef APPS_THREADS_MAX_HPP
#define APPS_THREADS_MAX_HPP

#include <cstdint>
#include <vector>

namespace apps {

    template<typename type>
    type max(const type * arr, const uint64_t first, const uint64_t last) {

        type m = arr[first];

        for (uint64_t i = first; i < last; ++i) {
            if (arr[i] > m) {
                m = arr[i];
            }
        }

        return m;

    }

    template<typename type>
    type max(const std::vector<type> & v, const uint64_t first, const uint64_t last) {
        type m = v[first];

        for (uint64_t i = first; i < last; ++i) {
            if (v[i] > m) {
                m = v[i];
            }
        }

        return m;
    }

}

#endif //APPS_THREADS_MAX_HPP
