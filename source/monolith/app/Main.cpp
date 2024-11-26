#include <iostream>

#include <sstream>
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

        executeCommand(args);
    }
}

}

}

int main() {
  monolith::app::Main();
}
