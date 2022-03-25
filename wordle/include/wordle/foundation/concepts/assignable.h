#ifndef WORDLE_FOUNDATION_CONCEPTS_ASSIGNABLE_H
#define WORDLE_FOUNDATION_CONCEPTS_ASSIGNABLE_H

#include <concepts>

namespace wordle::foundation::concepts {
template <typename To, typename From>
concept AssignableFrom = std::assignable_from<To, From>;

template <typename From, typename To>
concept AssignableTo = std::assignable_from<To, From>;

template <typename Type>
concept Copyable = std::copyable<Type>;

template <typename Type>
concept NonCopyable = !std::copyable<Type>;

}  // namespace wordle::foundation::concepts
#endif
