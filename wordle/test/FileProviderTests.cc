#include <gtest/gtest.h>
#include <wordle/foundation/filesystem/filesystem.h>

namespace wordle::foundation::filesystem::tests {

TEST(FileProvider, instance) {
  auto provider = FileProvider::instance();
  ASSERT_NE(provider, nullptr);
  ASSERT_EQ(provider, FileProvider::instance());
}

TEST(FileProvider, directory) {
  auto provider = FileProvider::instance();
}

}  // namespace wordle::foundation::filesystem::tests
