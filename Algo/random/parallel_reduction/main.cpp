#include <iostream>

void cumsum(int *input, int *output, int N) {
    auto sum = new int[N][40];

    // #pragma omp paralell for
    for (int i = 0; i < N; i++) sum[i][0] = input[i];

    for (int k = 1, layer = 0; k < N; k <<= 1, layer += 1) {
        // #pragma omp parallel for
        for (int i = 0; i < N; i++) {
            if (i + k < N) {
                sum[i][layer + 1] = sum[i][layer] + sum[i + k][layer];
            } else {
                sum[i][layer + 1] = sum[i][layer];
            }
        }
    }

    // #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        int total_sum = 0, bound = i + 1, ptr = 0;
        for (int layer = 20; layer >= 0; layer -= 1) {
            if (bound & (1 << layer)) {
                total_sum += sum[ptr][layer];
                ptr += (1 << layer);
            }
        }
        output[i] = total_sum;
    }
}

int main() {
    int input[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int output[8];
    cumsum(input, output, 8);
    for (int i = 0; i < 8; i++) std::cout << output[i] << " ";
    std::cout << std::endl;
}