#include <iostream>
#include <assert.h>
#include <chrono>
#include <random>


void swap(long& i, long& i1) {
    auto tmp = i;
    i = i1;
    i1 = tmp;
}

long* hoare_partition(long* first, long* last) {
    assert(first <= last);
    if (last - first < 2)
        return first; // nothing interesting to do
    --last;
    if (*first > *last)
        swap(*first, *last);
    auto pivot_pos = first;
    auto pivot = *pivot_pos;
    for (;;) {
        ++first;
        auto f = *first;
        while (f < pivot)
            f = *++first;
        auto l = *last;
        while (pivot < l)
            l = *--last;
        if (first >= last)
            break;
        *first = l;
        *last = f;
        --last;
    }
    --first;
    swap(*first, *pivot_pos);
    return first;
}

long* lomuto_partition_branchfree(long* first, long* last) {
    assert(first <= last);
    if (last - first < 2)
        return first; // nothing interesting to do
    --last;
    if (*first > *last)
        swap(*first, *last);
    auto pivot_pos = first;
    auto pivot = *first;
    do {
        ++first;
        assert(first <= last);
    } while (*first < pivot);
    for (auto read = first + 1; read < last; ++read) {
        auto x = *read;
        auto smaller = -int(x < pivot);
        auto delta = smaller & (read - first);
        first[delta] = *first;
        read[-delta] = x;
        first -= smaller;
    }
    assert(*first >= pivot);
    --first;
    *pivot_pos = *first;
    *first = pivot;
    return first;
}



int main() {
    int len = 1000000000;
    srand(time(0));
    long* arr1 = new long[len];
    long* arr2 = new long[len];
    for(int i = 0; i < len; i++){
        arr1[i] = arr2[i] = rand() % 200 - 100;
    }

    auto start = std::chrono::steady_clock::now();
    arr1 = hoare_partition(arr1, arr1 + len);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> delta1 = end - start;

    start = std::chrono::steady_clock::now();
    arr2 = lomuto_partition_branchfree(arr2, arr2 + len);
    end = std::chrono::steady_clock::now();
    std::chrono::duration<double> delta2 = end - start;

    std::cout << "Hoare partition time: " << delta1.count() << "\n";
    std::cout << "Lomuto branch-free partition time: " << delta2.count() << "\n";
}
