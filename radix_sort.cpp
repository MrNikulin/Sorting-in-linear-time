#include <vector>

void fast_sort(unsigned* begin, unsigned* end) {
    unsigned mask = 0b1111'1111;
    const size_t n = end - begin;
    unsigned mas1[2][256] = {};
    unsigned mas2[2][256] = {};
    unsigned mas3[2][256] = {};
    unsigned mas4[2][256] = {};
    for (size_t i = 0; i < n; ++i) {
        unsigned elem = *(begin + i);
        ++mas1[0][elem & mask];
        ++mas2[0][(elem >> 8) & mask];
        ++mas3[0][(elem >> 16) & mask];
        ++mas4[0][(elem >> 24)];
    }
    for (size_t i = 1; i < 256; ++i) {
        mas1[1][i] = mas1[0][i - 1] + mas1[1][i - 1];
        mas2[1][i] = mas2[0][i - 1] + mas2[1][i - 1];
        mas3[1][i] = mas3[0][i - 1] + mas3[1][i - 1];
        mas4[1][i] = mas4[0][i - 1] + mas4[1][i - 1];
    }
    std::vector<unsigned> tmp(n);
    for (size_t i = 0; i < n; ++i) {
        tmp[mas1[1][*(begin + i) & mask]++] = *(begin + i);
    }
    for (size_t i = 0; i < n; ++i) {
        *(begin + mas2[1][(tmp[i] >> 8) & mask]++) = tmp[i];
    }
    for (size_t i = 0; i < n; ++i) {
        tmp[mas3[1][(*(begin + i) >> 16) & mask]++] = *(begin + i);
    }
    for (size_t i = 0; i < n; ++i) {
        *(begin + mas4[1][tmp[i] >> 24]++) = tmp[i];
    }
}