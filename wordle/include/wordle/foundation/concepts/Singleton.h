#ifndef WORDLE_FOUNDATION_CONCEPTS_SINGLETON_H
#define WORDLE_FOUNDATION_CONCEPTS_SINGLETON_H

#include <wordle/foundation/concepts/Shareable.h>
#include <wordle/foundation/concepts/reflection.h>

namespace wordle::foundation::concepts {
template <typename Type>
concept Singleton = Shareable<Type> && requires {
  { Type::instance() } -> SameAs<typename Type::SharedPtr>;
};
}  // namespace wordle::foundation::concepts

#endif
