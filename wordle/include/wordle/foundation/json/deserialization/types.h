#ifndef WORDLE_FOUNDATION_JSON_DESERIALIZATION_TYPES_H
#define WORDLE_FOUNDATION_JSON_DESERIALIZATION_TYPES_H

#include <simdjson.h>

namespace wordle::foundation::json::deserialization {
using JsonArray = simdjson::ondemand::array;
using JsonDocument = simdjson::ondemand::document;
using JsonError = simdjson::simdjson_error;
using JsonErrorCode = simdjson::error_code;
using JsonField = simdjson::ondemand::field;
using JsonNumber = simdjson::ondemand::number;
using JsonNumberType = simdjson::ondemand::number_type;
using JsonObject = simdjson::ondemand::object;
using JsonParser = simdjson::ondemand::parser;
using JsonStream = simdjson::ondemand::document_stream;
using JsonType = simdjson::ondemand::json_type;
using JsonValue = simdjson::ondemand::value;

template <typename Value>
using JsonResult = simdjson::simdjson_result<Value>;
}  // namespace wordle::foundation::json::deserialization

#endif
