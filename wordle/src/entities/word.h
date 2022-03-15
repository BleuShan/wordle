#ifndef WORDLE_WORD_H
#define WORDLE_WORD_H

#include <string_view>

#include "prelude.h"

namespace wordle::entities {
class WORDLE_PUBLIC_API Word {
 public:
  Word(const char data[5]);
  Word(std::string_view data);

 private:
  char data_[5];
};
}  // namespace wordle::entities

#endif
