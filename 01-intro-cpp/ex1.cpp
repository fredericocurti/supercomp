#include <iostream>

int main() {
    int n;
    std::cout << "Quantos números?" << std::endl;
    std::cin >> n;
    float sum;
    float *n2 = new float[n];

    sum = 0;
    for (int i = 0; i < n; i++) {
        std::cout << "Insira um número" << std::endl;
        std::cin >> n2[i];
        sum += n2[i];
    }

    std::cout << "A média é: " << sum/n << std::endl;
    return 0;
}
