#ifndef WORDLE_FOUNDATION_CONCEPTS_CONVERTIBLE_H
#define WORDLE_FOUNDATION_CONCEPTS_CONVERTIBLE_H

#include <concepts>

namespace wordle::foundation::concepts {
template <typename From, typename To>
concept ConvertibleTo = std::convertible_to<From, To>;

template <typename From, typename To>
concept ConvertibleFrom = std::convertible_to<To, From>;
}  // namespace wordle::foundation::concepts

#endif
