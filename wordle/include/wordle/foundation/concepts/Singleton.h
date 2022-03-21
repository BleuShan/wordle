#ifndef WORDLE_FOUNDATION_CONCEPTS_SINGLETON_H
#define WORDLE_FOUNDATION_CONCEPTS_SINGLETON_H

#include <wordle/foundation/concepts/Shareable.h>

#include <concepts>

namespace wordle::foundation::concepts {
template <class MaybeSingleton>
concept Singleton = Shareable<MaybeSingleton> && requires {
  {
    MaybeSingleton::instance()
    } -> std::same_as<typename MaybeSingleton::SharedPtr>;
};
}  // namespace wordle::foundation::concepts

#endif
