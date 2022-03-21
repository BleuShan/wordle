#ifndef WORDLE_FOUNDATION_JSON_CONCEPTS_JSONDESERIALIZER_H
#define WORDLE_FOUNDATION_JSON_CONCEPTS_JSONDESERIALIZER_H

#include <wordle/foundation/concepts/concepts.h>
#include <wordle/foundation/json/types.h>

namespace wordle::foundation::concepts {
template <class MaybeJsonDeserializer>
concept JsonDeserializer =
    ConstructibleFrom<MaybeJsonDeserializer, json::JsonPaddedStringView> &&
    Shareable<typename MaybeJsonDeserializer::Output> &&
    requires(MaybeJsonDeserializer instance) {
  {
    instance()
    } -> SameAs<
        json::JsonResult<typename MaybeJsonDeserializer::Output::SharedPtr>>;
};
}  // namespace wordle::foundation::concepts

#endif
