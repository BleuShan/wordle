#ifndef WORDLE_DICTIONARY_H
#define WORDLE_DICTIONARY_H

#include <filesystem>
#include <memory>

#include "prelude.h"

namespace wordle {
using FilePath = std::filesystem::path;

class WORDLE_PUBLIC_API Dictionary : std::enable_shared_from_this<Dictionary> {
 public:
  using SharedPtr = std::shared_ptr<Dictionary>;
  inline SharedPtr share() { return shared_from_this(); }
  static SharedPtr load(FilePath path);

 private:
  Dictionary() = default;
};
}  // namespace wordle

#endif
