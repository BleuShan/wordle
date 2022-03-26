#ifndef WORDLE_FOUNDATION_MEMORY_H
#define WORDLE_FOUNDATION_MEMORY_H
#include <memory>

namespace wordle::foundation {
template <typename Type>
using StdUniquePtr = std::unique_ptr<Type>;

template <typename Type>
using StdSharedPtr = std::shared_ptr<Type>;

template <typename Type>
using StdWeakPtr = std::weak_ptr<Type>;
}  // namespace wordle::foundation

#endif
