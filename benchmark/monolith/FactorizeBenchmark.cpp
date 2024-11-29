#include "FactorizeBenchmark.hpp"

#include <chrono>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace benchmark {

std::vector<uint64_t> Factorize(uint64_t number) {
  std::vector<uint64_t> factors = std::vector<uint64_t>();

  for (uint64_t i = 2; i * i <= number; i++) {
    while (number % i == 0) {
      factors.push_back(i);
      number /= i;
    }
  }

  if (number != 1) {
    factors.push_back(number);
  }

  return factors;
}

void StartBenchmark() {
  for (uint64_t i = FROMVALUE; i <= TOVALUE; ++i) {
    const std::vector<uint64_t> primes = Factorize(i);
    if (i % LOGSTEP == 0) {
      std::cout << std::to_string(i) + " = ";
      for (const auto& prime : primes) {
        std::cout << std::to_string(prime) << "*";
      }
      std::cout << "\n";
    }
  }
}
}  // namespace benchmark

int main() {
  auto start = std::chrono::high_resolution_clock::now();

  benchmark::StartBenchmark();
  auto end = std::chrono::high_resolution_clock::now();

  const std::chrono::duration<double, std::micro> delay = end - start;

  std::cout << "Process duration: " << std::to_string(delay.count()) << "\n";
}