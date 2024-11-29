#include "IOBenchmark.hpp"

#include <unistd.h>

#include <chrono>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

namespace benchmark {
inline std::string GenerateTempFilename() {
  return "temp_test_file_" + std::to_string(getpid()) + ".bin";
}

int IOBenchmarkStart() {
  std::vector<char> data(BLOCKSIZE);
  std::random_device rand_device;
  std::mt19937 gen(rand_device());
  std::uniform_int_distribution<size_t> dist(0, (FILESIZE / BLOCKSIZE) - 1);
  std::uniform_int_distribution<int> data_dist(0, RANDOMMAX);

  for (size_t i = 0; i < BLOCKSIZE; ++i) {
    data[i] = static_cast<char>(data_dist(gen));
  }

  const std::string filename = GenerateTempFilename();

  std::ofstream file(filename, std::ios::binary | std::ios::out | std::ios::trunc);
  if (!file) {
    std::cerr << "Error during creating file: " << filename << "\n";
    return 1;
  }
  file.seekp(FILESIZE - 1);
  file.write("", 1);
  file.close();

  std::fstream test_file(filename, std::ios::binary | std::ios::in | std::ios::out);
  if (!test_file) {
    std::cerr << "Can't open file: " << filename << "\n";
    return 1;
  }

  std::vector<double> delays;
  for (size_t i = 0; i < NUMOPERATIONS; ++i) {
    const size_t block_index = dist(gen);
    const size_t offset = block_index * BLOCKSIZE;

    auto start = std::chrono::high_resolution_clock::now();
    test_file.seekp(offset);
    test_file.write(data.data(), BLOCKSIZE);
    test_file.flush();  // Обеспечивает запись на диск
    auto end = std::chrono::high_resolution_clock::now();

    const std::chrono::duration<double, std::micro> delay = end - start;
    delays.push_back(delay.count());
  }

  test_file.close();
  std::remove(filename.c_str());  // Удаляем временный файл

  double total_delay = 0;
  for (const double delay : delays) {
    total_delay += delay;
  }
  const double average_delay = total_delay / delays.size();

  std::cout << "Average delay: " << average_delay << " micro sec\n";

  return 0;
}
}  // namespace benchmark

int main() {
  benchmark::IOBenchmarkStart();
}