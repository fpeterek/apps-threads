//
// Created by Peterek, Filip on 08/11/2019.
//

#ifndef APPS_THREADS_COMPARATORS_HPP
#define APPS_THREADS_COMPARATORS_HPP

namespace apps {

    template<typename type>
    bool lt(const type & left, const type & right) {
        return left < right;
    }

    template<typename type>
    bool gt(const type & left, const type & right) {
        return left > right;
    }

}

#endif //APPS_THREADS_COMPARATORS_HPP
