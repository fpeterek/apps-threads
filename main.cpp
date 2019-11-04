#include <iostream>
#include <vector>

#include "max.hpp"
#include "sort.hpp"
#include "merge.hpp"

void max_test() {

    std::vector<int> v = {1, 3, 4, 2, 5};
    int * arr = new int[5];
    arr[0] = 1; arr[1] = 3; arr[2] = 4; arr[3] = 2; arr[4] = 5;

    int maxV = apps::max(v, 1, 4);
    int maxA = apps::max(arr, 1, 4);

    std::cout << "-------------- Max -----------------" << std::endl;
    std::cout << maxV << std::endl;
    std::cout << maxA << std::endl;

}

void sorted_test() {

    std::vector<int> v = {1, 3, 4, 2, 5};
    int * arr = new int[5];
    arr[0] = 1; arr[1] = 3; arr[2] = 4; arr[3] = 2; arr[4] = 5;

    std::vector<int> sorted = apps::sorted(v, 1, 3);

    std::cout << "-------------- Sorted -----------------" << std::endl;

    for (int i : sorted) {
        std::cout << i << " ";
    }
    std::endl(std::cout);

}

void bubblesort_test() {

    std::vector<int> v = {1, 3, 4, 2, 5};
    int * arr = new int[5];
    arr[0] = 1; arr[1] = 3; arr[2] = 4; arr[3] = 2; arr[4] = 5;

    std::cout << "-------------- BubbleSort -----------------" << std::endl;

    apps::bubbleSort(arr, 1, 4);
    apps::bubbleSort(v, 1, 4);

    std::cout << "Arr: " << std::endl;

    for (int i = 0; i < 5; ++i) {
        std::cout << arr[i] << " ";
    }
    std::endl(std::cout);

    std::cout << "Vec: " << std::endl;

    for (int i : v) {
        std::cout << i << " ";
    }
    std::endl(std::cout);

}

void merge_test() {

    std::vector<int> v = {1, 3, 4, 2, 5};
    int * arr = new int[5];
    arr[0] = 1; arr[1] = 3; arr[2] = 4; arr[3] = 2; arr[4] = 5;

    std::cout << "-------------- Merge -----------------" << std::endl;

    std::vector<int> v1 = apps::sorted(v, 0, 1);
    std::vector<int> v2 = apps::sorted(v, 2, 4);

    for (int i : v1) {
        std::cout << i << " ";
    }
    std::endl(std::cout);
    for (int i : v2) {
        std::cout << i << " ";
    }
    std::endl(std::cout);

    std::vector<int> m = apps::merge(v1, 0, 1, v2, 0, 2);
    for (int i : m) {
        std::cout << i << " ";
    }
    std::endl(std::cout);

}

void insertionsort_test() {

    std::vector<int> v = {3, 1, 5, 4, 2};
    int * arr = new int[5];
    arr[0] = 3; arr[1] = 1; arr[2] = 5; arr[3] = 4; arr[4] = 2;

    std::cout << "-------------- InsertionSort -----------------" << std::endl;

    apps::insertionSort(arr, 0, 4);
    apps::insertionSort(v, 0, 4);

    std::cout << "Arr: " << std::endl;

    for (int i = 0; i < 5; ++i) {
        std::cout << arr[i] << " ";
    }
    std::endl(std::cout);

    std::cout << "Vec: " << std::endl;

    for (int i : v) {
        std::cout << i << " ";
    }
    std::endl(std::cout);

}

int main() {

    max_test();
    sorted_test();
    bubblesort_test();
    merge_test();
    insertionsort_test();

}
