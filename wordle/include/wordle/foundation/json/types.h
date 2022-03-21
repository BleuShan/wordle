#ifndef WORDLE_FOUNDATION_JSON_TYPES_H
#define WORDLE_FOUNDATION_JSON_TYPES_H

#include <simdjson.h>

namespace wordle::foundation::json {
using JsonArray = simdjson::ondemand::array;
using JsonDocument = simdjson::ondemand::document;
using JsonErrorCode = simdjson::error_code;
using JsonField = simdjson::ondemand::field;
using JsonNumber = simdjson::ondemand::number;
using JsonNumberType = simdjson::ondemand::number_type;
using JsonObject = simdjson::ondemand::object;
using JsonPaddedString = simdjson::padded_string;
using JsonPaddedStringView = simdjson::padded_string_view;
using JsonParser = simdjson::ondemand::parser;
template <class Value>
using JsonResult = simdjson::simdjson_result<Value>;
using JsonStream = simdjson::ondemand::document_stream;
using JsonType = simdjson::ondemand::json_type;
using JsonValue = simdjson::ondemand::value;

using ParsedJsonValueResult = JsonResult<JsonValue>;
}  // namespace wordle::foundation::json

#endif
