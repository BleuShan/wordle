#ifndef WORDLE_FOUNDATION_CONCEPTS_STRING_H
#define WORDLE_FOUNDATION_CONCEPTS_STRING_H

#include <wordle/foundation/concepts/convertible.h>
#include <wordle/foundation/string.h>

#include <concepts>

namespace wordle::foundation::concepts {
template <typename Type>
concept StringConvertible = ConvertibleTo<foundation::String, Type>;

template <typename Type>
concept StdStringConvertible = ConvertibleTo<foundation::StdString, Type>;

template <typename Type>
concept StringViewConvertible = ConvertibleTo<foundation::StringView, Type>;
}  // namespace wordle::foundation::concepts

#endif
