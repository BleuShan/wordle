#ifndef WORDLE_FOUNDATION_JSON_CONCEPTS_JSON_DESERIALIZABLE_H
#define WORDLE_FOUNDATION_JSON_CONCEPTS_JSON_DESERIALIZABLE_H

#include <wordle/foundation/concepts/concepts.h>

namespace wordle::foundation::json::concepts {
template <class MaybeJsonDeserializable>
concept JsonDeserializable =
    foundation::concepts::Shareable<MaybeJsonDeserializable> &&
    requires(foundation::StringView path) {
  {
    MaybeJsonDeserializable::fromJSON(path)
    } -> std::same_as<typename MaybeJsonDeserializable::SharedPtr>;
};
}  // namespace wordle::foundation::json::concepts

#endif
