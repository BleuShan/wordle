#ifndef WORDLE_ENTIIES_DICTIONARY_H
#define WORDLE_ENTIIES_DICTIONARY_H

#include <wordle/foundation/foundation.h>
#include <wordle/prelude/prelude.h>

#include <filesystem>
#include <memory>
#include <string>
#include <unordered_set>

namespace wordle::entities {
using FilePath = std::filesystem::path;

class WORDLE_PUBLIC_API Dictionary final {
 public:
  inline bool empty() const noexcept { return data_.size() == 0; }
  inline bool add(foundation::StringView value) {
    foundation::String item;

    auto result = data_.insert(item);
    return result.second;
  }

 private:
  Dictionary() = default;
  std::unordered_set<foundation::String> data_;
};
}  // namespace wordle::entities

#endif
