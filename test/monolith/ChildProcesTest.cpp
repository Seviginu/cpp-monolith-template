#include <gtest/gtest.h>

#include "monolith/ChildProcess.hpp"

namespace monolith {

TEST(executeCommand, ExactMatch) {
  CreateChildProcess({"man"});
}

}  // namespace monolith