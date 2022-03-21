#ifndef WORDLE_FOUNDATION_CONCEPTS_CONVERTIBLE_H
#define WORDLE_FOUNDATION_CONCEPTS_CONVERTIBLE_H

#include <wordle/foundation/concepts/Shareable.h>

#include <concepts>

namespace wordle::foundation::concepts {
template <class From, class To>
concept ConvertibleFrom = std::convertible_to<From, To>;

template <class From, class To>
concept ConvertibleTo = std::convertible_to<To, From>;
}  // namespace wordle::foundation::concepts

#endif
