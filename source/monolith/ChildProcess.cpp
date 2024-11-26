#include "ChildProcess.hpp"
#include <sched.h>
#include <sys/wait.h>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <ctime>


namespace monolith {
struct ChildArgs {
    char** args;
};

int childFunction(void* arg) {
    auto* childArgs = reinterpret_cast<ChildArgs*>(arg);
    if (execvp(childArgs->args[0], childArgs->args) == -1) {
        perror("execvp failed");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

char** prepareArguments(const std::vector<std::string>& args) {
    char** cArgs = new char*[args.size() + 1];
    for (size_t i = 0; i < args.size(); ++i) {
        cArgs[i] = strdup(args[i].c_str());
    }
    cArgs[args.size()] = nullptr;
    return cArgs;
}

void freeArguments(char** args) {
    if (!args) return;
    for (size_t i = 0; args[i] != nullptr; ++i) {
        free(args[i]);
    }
    delete[] args;
}

int executeCommand(const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cerr << "No command provided.\n";
        return -1;
    }

    char** cArgs = prepareArguments(args);

    char* stack = static_cast<char*>(malloc(STACK_SIZE));
    if (!stack) {
        perror("malloc failed");
        freeArguments(cArgs);
        return -1;
    }

    char* stackTop = stack + STACK_SIZE;

    ChildArgs childArgs = {cArgs};

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    pid_t pid = clone(childFunction, stackTop, SIGCHLD, &childArgs);
    if (pid < 0) {
        perror("clone failed");
        free(stack);
        freeArguments(cArgs);
        return -1;
    }

    int status;
    if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid failed");
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsedTime = (end.tv_sec - start.tv_sec) +
                         (end.tv_nsec - start.tv_nsec) / 1e9;
    std::cout << "Execution time: " << elapsedTime << " seconds\n";

    free(stack);
    freeArguments(cArgs);

    return WEXITSTATUS(status);
}
}
