#ifndef WORDLE_FOUNDATION_JSON_INL_H
#define WORDLE_FOUNDATION_JSON_INL_H

#ifndef WORDLE_FOUNDATION_JSON_H
  #error "Must be included from wordle/foundation/json/json.h"
#endif

namespace wordle::foundation::json {

constexpr auto kJsonStringPadding = simdjson::SIMDJSON_PADDING;

template <concepts::JsonDeserializable Output> requires concepts::Singleton<typename Output::JsonDeserializer>
auto deserialize(JsonPaddedStringView paddedRawJson) {
  auto instance = Output::JsonDeserializer::instance();
  return instance->deserialize(paddedRawJson);
}

template <concepts::JsonDeserializable Output> requires concepts::DefaultInitializable<typename Output::JsonDeserializer>
auto deserialize(JsonPaddedStringView paddedRawJson) {
   typename Output::JsonDeserializer instance{};
  return instance.deserialize(paddedRawJson);
}

template <concepts::JsonDeserializable Output>
auto deserialize(foundation::StringView rawJson) {
  auto paddedRawJson =
      JsonPaddedStringView{rawJson, rawJson.size() + kJsonStringPadding};

  return deserialize<Output>(paddedRawJson);
}

}  // namespace wordle::foundation::json

#endif
