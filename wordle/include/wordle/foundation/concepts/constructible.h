#ifndef WORDLE_FOUNDATION_CONCEPTS_CONSTRUCTIBLE_H
#define WORDLE_FOUNDATION_CONCEPTS_CONSTRUCTIBLE_H

#include <concepts>

namespace wordle::foundation::concepts {
template <class Type, class... Args>
concept ConstructibleFrom = std::constructible_from<Type, Args...>;

template <class Type>
concept CopyConstructible = std::copy_constructible<Type>;

template <class Type>
concept MoveConstructible = std::move_constructible<Type>;

}  // namespace wordle::foundation::concepts

#endif
