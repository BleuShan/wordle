#ifndef WORDLE_FOUNDATION_CONCEPTS_SHAREABLE_H
#define WORDLE_FOUNDATION_CONCEPTS_SHAREABLE_H

#include <wordle/foundation/concepts/constructible.h>
#include <wordle/foundation/concepts/reflection.h>

#include <memory>

namespace wordle::foundation::concepts {
template <class Type>
concept Shareable = !DefaultInitializable<Type> &&
                    SameAs<typename Type::SharedPtr, std::shared_ptr<Type>> &&
                    SameAs<typename Type::WeakPtr, std::weak_ptr<Type>> &&
                    requires(Type instance) {
  { instance.shared_from_this() } -> SameAs<typename Type::SharedPtr>;
  { instance.weak_from_this() } -> SameAs<typename Type::WeakPtr>;
};

}  // namespace wordle::foundation::concepts

#endif
