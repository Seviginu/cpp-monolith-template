#include <cstdint>
#include <vector>

namespace benchmark {
const uint64_t FROMVALUE = 3;
const uint64_t TOVALUE = 1000000000;
const uint64_t LOGSTEP = 10000000;

std::vector<uint64_t> Factorize(uint64_t number);
void StartBenchmark();
}  // namespace benchmark