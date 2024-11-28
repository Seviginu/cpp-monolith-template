#include <gtest/gtest.h>

#include "monolith/ChildProcess.hpp"

namespace monolith {

TEST(executeCommand, ExactMatch) {
  ASSERT_EQ(executeCommand({"ls"}), 0);
}

}  // namespace monolith