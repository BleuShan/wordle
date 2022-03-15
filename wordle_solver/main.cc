#include <memory>

#include "wordle.h"

using namespace wordle::managers;

int main(int argc, char const *argv[]) {
  auto dictionnaries = std::make_unique<DictionaryManager>();
  return 0;
}
