#ifndef WORDLE_FOUNDATION_JSON_INL_H
#define WORDLE_FOUNDATION_JSON_INL_H

#ifndef WORDLE_FOUNDATION_JSON_H
  #error "Must be included from wordle/foundation/json/json.h"
#endif

namespace wordle::foundation::json {

constexpr auto kJsonStringPadding = simdjson::SIMDJSON_PADDING;

template <concepts::JsonDeserializable Object>
auto deserialize(JsonPaddedStringView paddedRawJson) {
  return typename Object::JsonDeserializer(paddedRawJson)();
}

template <concepts::JsonDeserializable Object>
auto deserialize(foundation::StringView rawJson) {
  auto paddedRawJson =
      JsonPaddedStringView{rawJson, rawJson.size() + kJsonStringPadding};

  return deserialize<Object>(paddedRawJson);
}

}  // namespace wordle::foundation::json

#endif
