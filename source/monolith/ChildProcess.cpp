#include "ChildProcess.hpp"

#include <sched.h>
#include <sys/types.h>
#include <unistd.h>

#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

namespace monolith {

int CloneFunction(void* arg) {
  const char** args = static_cast<const char**>(arg);
  if (execvp(args[0], const_cast<char* const*>(args)) == -1) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

pid_t CreateChildProcess(const std::vector<std::string>& arguments) {
  std::vector<const char*> argv;
  argv.reserve(arguments.size() + 2);
  for (const auto& arg : arguments) {
    argv.push_back(arg.c_str());
  }
  argv.push_back(nullptr);

  auto stack = std::make_unique<char[]>(STACKSIZE);
  void* stack_top = stack.get() + STACKSIZE;

  const pid_t pid = clone(CloneFunction, stack_top, SIGCHLD, argv.data());

  return pid;
}

}  // namespace monolith
