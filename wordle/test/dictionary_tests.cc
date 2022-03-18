
#include <gtest/gtest.h>

#include <filesystem>
#include <memory>

#include "wordle/dictionary.h"

using wordle::Dictionary;
using wordle::FilePath;
using FilePathSharedPtr = std::shared_ptr<FilePath>;
namespace filesystem = std::filesystem;

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
  const auto current_path = filesystem::current_path();
  const auto filepath = get_wordle_wordlist_json_filepath(current_path);
  if (filepath == nullptr) {
    FAIL();
  }

  const auto dict = Dictionary::load(*filepath);
  ASSERT_NE(dict, nullptr);
  ASSERT_FALSE(dict->empty());
}
