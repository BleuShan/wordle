#ifndef WORDLE_FOUNDATION_CONCEPTS_SHAREABLE_H
#define WORDLE_FOUNDATION_CONCEPTS_SHAREABLE_H

#include <concepts>
#include <memory>

namespace wordle::foundation::concepts {
template <class T>
concept Shareable = requires(T* instance) {
  typename T::SharedPtr;
  typename T::WeakPtr;
  std::same_as<typename T::SharedPtr, std::shared_ptr<T>>;
  std::same_as<typename T::WeakPtr, std::weak_ptr<T>>;
  { instance->shared_from_this() } -> std::same_as<typename T::SharedPtr>;
  { instance->weak_from_this() } -> std::same_as<typename T::WeakPtr>;
};

}  // namespace wordle::foundation::concepts

#endif
