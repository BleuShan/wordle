#include <simdjson.h>
#include <wordle/entities/Dictionary.h>

#include <memory>

namespace filesystem = std::filesystem;
using JsonParser = simdjson::dom::parser;
using JsonElement = simdjson::dom::element;
using JsonErrorCode = simdjson::error_code;

namespace wordle {}  // namespace wordle
