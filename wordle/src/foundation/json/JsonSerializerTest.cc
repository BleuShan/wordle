#include <gtest/gtest.h>
#include <wordle/foundation/json/json.h>

#include <thread>

namespace wordle::foundation::json::tests {

TEST(JsonSerializer, instance) {
  auto main = &JsonSerializer::instance();
  auto success = std::atomic_bool{false};
  auto run = [&success](JsonSerializer* other) {
    auto current = &JsonSerializer::instance();
    success = current != nullptr && current != other;
  };
  auto thread = std::thread{run, main};
  thread.join();
  ASSERT_NE(main, nullptr);
  ASSERT_TRUE(success);
}

}  // namespace wordle::foundation::json::tests
