#ifndef WORDLE_WORD_H
#define WORDLE_WORD_H

#include <string_view>

#include "../prelude.h"

namespace wordle::entities {
class WORDLE_PUBLIC_API Word {
 public:
  constexpr static const size_t MAX_SIZE = sizeof(char[5]);

  Word();
  Word(std::string_view str);
  Word(const Word& other);
  ~Word();

  Word& operator=(const Word& other);
  constexpr const char operator[](size_t index) const { return data_[index]; }
  constexpr operator std::string_view() const {
    return std::string_view{data_};
  }

 private:
  char* data_;
};
}  // namespace wordle::entities

#endif
