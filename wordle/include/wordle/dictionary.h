#ifndef WORDLE_DICTIONARY_H
#define WORDLE_DICTIONARY_H

#include <filesystem>
#include <memory>
#include <string>
#include <unordered_set>

#include "prelude.h"

namespace wordle {
using FilePath = std::filesystem::path;
using String = std::string;
using StringView = std::string_view;

class WORDLE_PUBLIC_API Dictionary : std::enable_shared_from_this<Dictionary> {
 public:
  using SharedPtr = std::shared_ptr<Dictionary>;
  static SharedPtr load(const FilePath& path);

  inline SharedPtr share() { return shared_from_this(); }
  inline bool empty() const { return data_.size() == 0; }
  inline bool add(StringView value) {
    String item = String(value);
    auto result = data_.insert(item);
    return result.second;
  }

 private:
  Dictionary() = default;
  std::unordered_set<std::string> data_;
};
}  // namespace wordle

#endif
