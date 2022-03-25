#ifndef WORDLE_FOUNDATION_CONCEPTS_CONSTRUCTIBLE_H
#define WORDLE_FOUNDATION_CONCEPTS_CONSTRUCTIBLE_H

#include <concepts>

namespace wordle::foundation::concepts {
template <typename Type, typename... Args>
concept ConstructibleFrom = std::constructible_from<Type, Args...>;

template <typename Type>
concept CopyConstructible = std::copy_constructible<Type>;

template <typename Type>
concept MoveConstructible = std::move_constructible<Type>;

template <typename Type>
concept DefaultInitializable = std::default_initializable<Type>;

template <typename Type>
concept Destructible = std::destructible<Type>;

}  // namespace wordle::foundation::concepts

#endif
