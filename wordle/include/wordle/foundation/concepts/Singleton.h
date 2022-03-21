#ifndef WORDLE_FOUNDATION_CONCEPTS_SINGLETON_H
#define WORDLE_FOUNDATION_CONCEPTS_SINGLETON_H

#include <wordle/foundation/concepts/Shareable.h>

#include <concepts>

namespace wordle::foundation::concepts {
template <class T>
concept Singleton = Shareable<T> && requires {
  { T::instance() } -> std::same_as<typename T::SharedPtr>;
};
}  // namespace wordle::foundation::concepts

#endif
