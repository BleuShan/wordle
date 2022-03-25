#ifndef WORDLE_FOUNDATION_JSON_CONCEPTS_JSONDESERIALIZABLE_H
#define WORDLE_FOUNDATION_JSON_CONCEPTS_JSONDESERIALIZABLE_H

#include <wordle/foundation/concepts/concepts.h>
#include <wordle/foundation/json/concepts/JsonDeserializer.h>
#include <wordle/foundation/json/types.h>

namespace wordle::foundation::concepts {
template <typename Type>
concept JsonDeserializable = Shareable<Type> &&
    JsonDeserializer<Type, typename Type::JsonDeserializer> ||
    JsonDeserializer<typename Type::SharedPtr, typename Type::JsonDeserializer>;

}  // namespace wordle::foundation::concepts

#endif
