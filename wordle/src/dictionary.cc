#include "wordle/dictionary.h"

#include <simdjson.h>

#include <memory>

namespace filesystem = std::filesystem;
using JsonParser = simdjson::dom::parser;
using JsonElement = simdjson::dom::element;
using JsonErrorCode = simdjson::error_code;

namespace wordle {
Dictionary::Handle Dictionary::load(const FilePath& path) {
  if (!filesystem::exists(path)) {
    return nullptr;
  }

  JsonParser parser;
  auto path_value = path.string();
  auto document = parser.load(path_value);
  if (!document.is_object()) {
    return nullptr;
  }

  auto anwsers = document["anwsers"];
  if (!anwsers.is_array()) {
    return nullptr;
  }

  auto allowed_words = document["allowed_words"];
  if (!allowed_words.is_array()) {
    return nullptr;
  }
  auto dict = Handle{new Dictionary()};
  for (auto&& element : anwsers) {
    auto result = element.get_string();
    if (result.error() == JsonErrorCode::INCORRECT_TYPE) {
      continue;
    }
    dict->add(result.value());
  }

  for (auto&& element : allowed_words) {
    auto result = element.get_string();
    if (result.error() == JsonErrorCode::INCORRECT_TYPE) {
      continue;
    }
    dict->add(result.value());
  }

  return dict;
}
}  // namespace wordle
