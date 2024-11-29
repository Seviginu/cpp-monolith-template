#include <sys/wait.h>

#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "monolith/ChildProcess.hpp"

namespace monolith::app {

namespace {

void Main() {
  std::string input;

  while (true) {
    std::cout << "custom_shell> ";
    if (!std::getline(std::cin, input)) {
      break;
    }

    std::istringstream iss(input);
    std::vector<std::string> args;
    std::string token;
    while (iss >> token) {
      args.push_back(token);
    }

    if (args.empty()) {
      continue;
    }

    if (args[0] == "exit") {
      break;
    }

    auto start = std::chrono::high_resolution_clock::now();

    const pid_t pid = CreateChildProcess(args);

    int status = 0;
    if (waitpid(pid, &status, 0) == -1) {
      std::cout << "Failed to wait for child process\n";
      continue;
    }

    if (WIFEXITED(status)) {
      std::cout << "----------------------------------------\n";
      auto end = std::chrono::high_resolution_clock::now();
      const std::chrono::duration<double> elapsed = end - start;
      std::cout << "Process time: " << elapsed.count() << " seconds\n";

    } else {
      std::cout << "Child process did not exit normally\n";
    }
  }
}

}  // namespace

}  // namespace monolith::app

int main() {
  monolith::app::Main();
}
