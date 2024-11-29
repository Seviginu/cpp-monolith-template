
#include <string>
#include <vector>

namespace monolith {
int CloneFunction(void* arg);

pid_t CreateChildProcess(const std::vector<std::string>& arguments);

constexpr size_t STACKSIZE = 1048576;  // 1 МБ
};  // namespace monolith
