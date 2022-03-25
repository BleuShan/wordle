#include <gtest/gtest.h>
#include <wordle/foundation/filesystem/providers/FileProvider.h>

namespace wordle::foundation::filesystem::providers::tests {

TEST(FileProvider, currentDirectory) {
  auto provider = FileProvider::currentDirectory();
  ASSERT_NE(provider, nullptr);
  ASSERT_EQ(provider, FileProvider::currentDirectory());
}

TEST(FileProvider, path) {
  auto provider = FileProvider::currentDirectory();
  ASSERT_EQ(provider->path(), std::filesystem::current_path());
}

}  // namespace wordle::foundation::filesystem::providers::tests
