#include <folly/SingletonThreadLocal.h>
#include <wordle/foundation/json/JsonSerializer.h>

using wordle::foundation::json::JsonSerializer;

auto JsonSerializer::instance() -> JsonSerializer& {
  return folly::SingletonThreadLocal<JsonSerializer>::get();
}
