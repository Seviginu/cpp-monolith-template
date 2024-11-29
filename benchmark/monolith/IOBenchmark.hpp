#include <string>

namespace benchmark {
const size_t BLOCKSIZE = 4096;              // 4 KB
const size_t FILESIZE = 1024 * 1024 * 100;  // 100 MB
const size_t NUMOPERATIONS = 100000;        // Количество операций записи
const size_t RANDOMMAX = 255;               // Количество операций записи

inline std::string GenerateTempFilename();
int IOBenchmarkStart();

}  // namespace benchmark
