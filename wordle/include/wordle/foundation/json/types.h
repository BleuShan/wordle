#ifndef WORDLE_FOUNDATION_JSON_TYPES_H
#define WORDLE_FOUNDATION_JSON_TYPES_H

#include <simdjson.h>

namespace wordle::foundation::json {
using JsonParser = simdjson::ondemand::parser;
using JsonDocument = simdjson::ondemand::document;
using JsonDocumentRef = simdjson::ondemand::document_reference;
using JsonStream = simdjson::ondemand::document_stream;
using JsonValue = simdjson::ondemand::value;
}  // namespace wordle::foundation::json

#endif
