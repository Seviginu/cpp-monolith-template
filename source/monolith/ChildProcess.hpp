
#include <vector>
#include <string>

namespace monolith {
    int executeCommand(const std::vector<std::string>& args);

    char** prepareArguments(const std::vector<std::string>& args);

    void freeArguments(char** args);

    int childFunction(void* arg);

    constexpr size_t STACK_SIZE = 1024 * 1024; // 1 МБ
};

