#ifndef WORDLE_FOUNDATION_CONCEPTS_STRING_H
#define WORDLE_FOUNDATION_CONCEPTS_STRING_H

#include <wordle/foundation/concepts/convertible.h>
#include <wordle/foundation/string.h>

#include <concepts>

namespace wordle::foundation::concepts {
template <class MaybeStringConvertible>
concept StringConvertible =
    ConvertibleTo<foundation::String, MaybeStringConvertible>;

template <class MaybeStdStringConvertible>
concept StdStringConvertible =
    ConvertibleTo<foundation::StdString, MaybeStdStringConvertible>;
}  // namespace wordle::foundation::concepts

#endif
