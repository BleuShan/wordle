#ifndef WORDLE_FOUNDATION_JSON_CONCEPTS_JSONDESERIALIZABLE_H
#define WORDLE_FOUNDATION_JSON_CONCEPTS_JSONDESERIALIZABLE_H

#include <wordle/foundation/concepts/concepts.h>
#include <wordle/foundation/json/concepts/JsonDeserializer.h>
#include <wordle/foundation/json/types.h>

namespace wordle::foundation::concepts {
template <class MaybeJsonDeserializable>
concept JsonDeserializable = Shareable<MaybeJsonDeserializable> &&
    JsonDeserializer<typename MaybeJsonDeserializable::JsonDeserializer> &&
    SameAs<typename MaybeJsonDeserializable::JsonDeserializer::Output,
           MaybeJsonDeserializable>;
}  // namespace wordle::foundation::concepts

#endif
