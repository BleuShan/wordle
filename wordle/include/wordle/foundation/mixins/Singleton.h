#ifndef WORDLE_FOUNDATION_MIXINS_SINGLETON_H
#define WORDLE_FOUNDATION_MIXINS_SINGLETON_H

#include <wordle/foundation/mixins/Shareable.h>

namespace wordle::foundation::mixins {
template <class T>
class Singleton : public Shareable<T> {
 public:
  static auto instance() -> typename Shareable<T>::SharedPtr;

 protected:
  Singleton() = default;
};
}  // namespace wordle::foundation::mixins

#endif
