#ifndef WORDLE_FOUNDATION_SHAREABLE_OBJECT_H
#define WORDLE_FOUNDATION_SHAREABLE_OBJECT_H

#include <memory>

namespace wordle::foundation {
template <class T>
class ShareableObject : std::enable_shared_from_this<T> {
 public:
  using Handle = std::shared_ptr<T>;
  using WeakHandle = std::weak_ptr<T>;

  auto share() -> Handle { return this->shared_from_this(); }

  auto share_weak() -> WeakHandle { return this->weak_from_this(); }

 protected:
  constexpr ShareableObject() noexcept : std::enable_shared_from_this<T>() {}
  auto operator=(const ShareableObject&) noexcept -> ShareableObject& {
    return *this;
  }
  ~ShareableObject() = default;
};
}  // namespace wordle::foundation

#endif
