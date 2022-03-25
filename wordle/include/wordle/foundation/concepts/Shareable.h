#ifndef WORDLE_FOUNDATION_CONCEPTS_SHAREABLE_H
#define WORDLE_FOUNDATION_CONCEPTS_SHAREABLE_H

#include <wordle/foundation/concepts/constructible.h>
#include <wordle/foundation/concepts/reflection.h>

#include <wordle/foundation/memory.h>

namespace wordle::foundation::concepts {
template <typename Type>
concept Shareable = !DefaultInitializable<Type> &&
                    SameAs<typename Type::SharedPtr, StdSharedPtr<Type>> &&
                    SameAs<typename Type::WeakPtr, StdWeakPtr<Type>> &&
                    requires(Type instance) {
  { instance.shared_from_this() } -> SameAs<typename Type::SharedPtr>;
  { instance.weak_from_this() } -> SameAs<typename Type::WeakPtr>;
};

}  // namespace wordle::foundation::concepts

#endif
