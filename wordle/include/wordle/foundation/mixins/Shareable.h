#ifndef WORDLE_FOUNDATION_MIXINS_SHAREABLE_H
#define WORDLE_FOUNDATION_MIXINS_SHAREABLE_H

#include <memory>

namespace wordle::foundation::mixins {
template <class T>
class Shareable : public std::enable_shared_from_this<T> {
 public:
  using SharedPtr = std::shared_ptr<T>;
  using WeakPtr = std::weak_ptr<T>;

  [[nodiscard]] auto constexpr share() -> SharedPtr {
    return this->shared_from_this();
  }

  [[nodiscard]] auto constexpr share_weak() -> WeakPtr {
    return this->shared_weak_from_this();
  }

 protected:
  constexpr Shareable() noexcept = default;
};
}  // namespace wordle::foundation::mixins

#endif
