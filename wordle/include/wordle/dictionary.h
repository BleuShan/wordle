#ifndef WORDLE_DICTIONARY_H
#define WORDLE_DICTIONARY_H

#include <filesystem>
#include <memory>
#include <string>
#include <unordered_set>

#include "wordle/foundation.h"

namespace wordle {
using FilePath = std::filesystem::path;

class WORDLE_PUBLIC_API Dictionary
    : public foundation::ShareableObject<Dictionary> {
 public:
  static Handle load(const FilePath& path);
  inline bool empty() const { return data_.size() == 0; }
  inline bool add(foundation::StringView value) {
    auto item = foundation::String(value);
    auto result = data_.insert(item);
    return result.second;
  }

 private:
  Dictionary() = default;
  std::unordered_set<std::string> data_;
};
}  // namespace wordle

#endif
