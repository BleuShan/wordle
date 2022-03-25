#ifndef WORDLE_FOUNDATION_JSON_DESERIALIZE_H
#define WORDLE_FOUNDATION_JSON_DESERIALIZE_H

#include <wordle/foundation/json/concepts/concepts.h>

namespace wordle::foundation::json {

constexpr auto kJsonStringPadding = simdjson::SIMDJSON_PADDING;

template <concepts::JsonDeserializable Output>
requires concepts::Singleton<typename Output::JsonDeserializer>
auto deserialize(PaddedStringView paddedRawJson) {
  auto instance = Output::JsonDeserializer::instance();
  return instance->deserialize(paddedRawJson);
}

template <concepts::JsonDeserializable Output>
requires concepts::DefaultInitializable<typename Output::JsonDeserializer>
auto deserialize(PaddedStringView paddedRawJson) {
  typename Output::JsonDeserializer instance{};
  return instance.deserialize(paddedRawJson);
}

template <concepts::JsonDeserializable Output>
auto deserialize(foundation::StringView rawJson) {
  PaddedString paddedRawJson{rawJson};

  return deserialize<Output>(paddedRawJson);
}

}  // namespace wordle::foundation::json

#endif
