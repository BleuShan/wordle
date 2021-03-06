#ifndef WORDLE_FOUNDATION_JSON_CONCEPTS_JSONDESERIALIZER_H
#define WORDLE_FOUNDATION_JSON_CONCEPTS_JSONDESERIALIZER_H

#include <wordle/foundation/concepts/concepts.h>
#include <wordle/foundation/json/types.h>

namespace wordle::foundation::concepts {
template <typename Output, typename Type>
concept JsonDeserializer = requires(Type instance, PaddedStringView rawJson) {
  { instance.deserialize(rawJson) } -> SameAs<Output>;
};
}  // namespace wordle::foundation::concepts

#endif
