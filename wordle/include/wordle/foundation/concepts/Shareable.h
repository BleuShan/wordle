#ifndef WORDLE_FOUNDATION_CONCEPTS_SHAREABLE_H
#define WORDLE_FOUNDATION_CONCEPTS_SHAREABLE_H

#include <wordle/foundation/concepts/reflection.h>

#include <memory>

namespace wordle::foundation::concepts {
template <class MaybeShareable>
concept Shareable = requires(MaybeShareable instance) {
  typename MaybeShareable::SharedPtr;
  typename MaybeShareable::WeakPtr;
  SameAs<typename MaybeShareable::SharedPtr, std::shared_ptr<MaybeShareable>>;
  SameAs<typename MaybeShareable::WeakPtr, std::weak_ptr<MaybeShareable>>;
  { instance.shared_from_this() } -> SameAs<typename MaybeShareable::SharedPtr>;
  { instance.weak_from_this() } -> SameAs<typename MaybeShareable::WeakPtr>;
};

}  // namespace wordle::foundation::concepts

#endif
