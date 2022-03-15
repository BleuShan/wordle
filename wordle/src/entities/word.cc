#include "wordle/entities/word.h"

#include <memory>
namespace wordle::entities {
Word::Word() : data_(new char[MAX_SIZE]) {}

Word::Word(const Word& other) : Word() {
  std::memcpy(data_, other.data_, MAX_SIZE);
}

Word::Word(std::string_view str) : Word() {
  if (str.size() >= MAX_SIZE) {
    std::memcpy(data_, str.data(), MAX_SIZE);
  }
}

Word::~Word() {
  delete[] data_;
}

Word& Word::operator=(const Word& other) {
  return *this = Word(other);
}
}  // namespace wordle::entities
