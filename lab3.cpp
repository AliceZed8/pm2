#include <iostream>
#include <vector>

int main()
{
    uint64_t x;
    std::cin >> x;
    std::vector<uint64_t> result;
    uint64_t maxK = log(x) / log(3);
    uint64_t maxL = log(x) / log(5);
    uint64_t maxM = log(x) / log(7);
    for (uint64_t K = 0; K <= maxK; K++) {
        for (uint64_t L = 0; L <= maxL; L++) {
            for (uint64_t M = 0; M <= maxM; M++) {
                uint64_t number = pow(3, K) * pow(5, L) * pow(7, M);
                if (number <= x) {
                    result.push_back(number);
                }
            }
        }
    }
    
    for (int num : result) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

}
