
#include <gtest/gtest.h>
#include <wordle/entities/Dictionary.h>

#include <filesystem>
#include <memory>

namespace filesystem = std::filesystem;

using FilePath = filesystem::path;
using wordle::entities::Dictionary;
using FilePathSharedPtr = std::shared_ptr<FilePath>;
namespace wordle::entities::tests {

FilePathSharedPtr append_wordle_wordlist_json_filepath(const FilePath& path) {
  auto filepath = std::make_shared<FilePath>(path);
  filepath->append("data").append("wordle_wordlist.json");
  if (!filesystem::exists(*filepath)) {
    return nullptr;
  }

  return filepath;
}

FilePathSharedPtr get_wordle_wordlist_json_filepath(const FilePath& path) {
  auto current_path = path;
  auto filepath = append_wordle_wordlist_json_filepath(path);
  while (filepath == nullptr && current_path.has_parent_path()) {
    current_path = current_path.parent_path();
    filepath = append_wordle_wordlist_json_filepath(current_path);
  }

  return filepath;
}

TEST(Dictionary, load) {
  GTEST_SKIP();
  const auto current_path = filesystem::current_path();
  const auto filepath = get_wordle_wordlist_json_filepath(current_path);
  if (filepath == nullptr) {
    FAIL();
  }

  ASSERT_NE(filepath, nullptr);
}

}  // namespace wordle::entities::tests
