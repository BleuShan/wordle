#include <gtest/gtest.h>
#include <wordle/foundation/filesystem/filesystem.h>

namespace wordle::foundation::filesystem::tests {

TEST(FileManager, instance) {
  auto manager = FileManager::instance();
  ASSERT_NE(manager, nullptr);
  ASSERT_EQ(manager, FileManager::instance());
}

}  // namespace wordle::foundation::filesystem::tests
