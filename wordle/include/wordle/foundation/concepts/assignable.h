#ifndef WORDLE_FOUNDATION_CONCEPTS_ASSIGNABLE_H
#define WORDLE_FOUNDATION_CONCEPTS_ASSIGNABLE_H

#include <concepts>

namespace wordle::foundation::concepts {
template <class To, class From>
concept AssignableFrom = std::assignable_from<To, From>;

template <class From, class To>
concept AssignableTo = std::assignable_from<To, From>;

template <class Type>
concept Copyable = std::copyable<Type>;

template <class Type>
concept NonCopyable = !std::copyable<Type>;

}  // namespace wordle::foundation::concepts
#endif
