//
// Created by Filip Peterek on 03/11/2019.
//

#ifndef APPS_THREADS_MERGE_HPP
#define APPS_THREADS_MERGE_HPP

#include <cstdint>
#include <vector>

namespace apps {

    template<typename type>
    type * merge(type * a1, const uint64_t f1, const uint64_t l1,
                 type * a2, const uint64_t f2, const uint64_t l2,
                 std::function<bool(const type &, const type &)> cmp) {

        const uint64_t mergedSize = (l1 - f1) + (l2 - f2);
        type * m = new type[mergedSize];

        uint64_t i1 = f1;
        uint64_t i2 = f2;

        uint64_t mi = 0;

        while (i1 < l1 or i2 < l2) {

            if (i1 >= l1) {
                m[mi] = a2[i2];
                ++i2;
            }
            else if (i2 >= l2) {
                m[mi] = a1[i1];
                ++i1;
            }
            else if (cmp(a1[i1], a2[i2])) {
                m[mi] = a2[i2];
                ++i2;
            }
            else {
                m[mi] = a1[i1];
                ++i1;
            }

            ++mi;

        }

        return m;

    }

    template<typename type>
    std::vector<type> merge(const std::vector<type> & a1, const uint64_t f1, const uint64_t l1,
                            const std::vector<type> & a2, const uint64_t f2, const uint64_t l2,
                            std::function<bool(const type &, const type &)> cmp) {

        std::vector<type> m;

        uint64_t i1 = f1;
        uint64_t i2 = f2;

        while (i1 <= l1 or i2 <= l2) {

            if (i1 > l1) {
                m.emplace_back(a2[i2]);
                ++i2;
            }
            else if (i2 > l2) {
                m.emplace_back(a1[i1]);
                ++i1;
            }
            else if (cmp(a1[i1], a2[i2])) {
                m.emplace_back(a2[i2]);
                ++i2;
            }
            else {
                m.emplace_back(a1[i1]);
                ++i1;
            }

        }

        return m;

    }

    template<typename type>
    void mergeInto(
            const std::vector<type> & a1, const uint64_t f1, const uint64_t l1,
            const std::vector<type> & a2, const uint64_t f2, const uint64_t l2,
            std::vector<type> & dst, size_t offset,
            std::function<bool(const type &, const type &)> cmp) {

        auto iter = dst.begin() + offset;

        uint64_t i1 = f1;
        uint64_t i2 = f2;

        while (i1 <= l1 or i2 <= l2) {

            if (i1 > l1) {
                dst.insert(iter++, a2[i2]);
                ++i2;
            }
            else if (i2 > l2) {
                dst.insert(iter++, a1[i1]);
                ++i1;
            }
            else if (cmp(a1[i1], a2[i2])) {
                dst.insert(iter++, a2[i2]);
                ++i2;
            }
            else {
                dst.insert(iter++, a1[i1]);
                ++i1;
            }

        }

    }

}

#endif //APPS_THREADS_MERGE_HPP
