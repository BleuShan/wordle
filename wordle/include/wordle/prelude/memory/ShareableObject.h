#ifndef WORDLE_PRELUDE_MEMORY_SHAREABLE_OBJECT_H
#define WORDLE_PRELUDE_MEMORY_SHAREABLE_OBJECT_H

#include <memory>

namespace wordle {
template <class T>
class ShareableObject : protected std::enable_shared_from_this<T> {
 public:
  using Handle = std::shared_ptr<T>;
  using WeakHandle = std::weak_ptr<T>;

  [[nodiscard]] Handle share() { return this->shared_from_this(); }
  [[nodiscard]] WeakHandle share_weak() { return this->weak_from_this(); }

 protected:
  constexpr ShareableObject() noexcept : std::enable_shared_from_this<T>() {}
  ShareableObject& operator=(const ShareableObject&) noexcept { return *this; }
  ~ShareableObject() = default;
};
}  // namespace wordle

#endif
