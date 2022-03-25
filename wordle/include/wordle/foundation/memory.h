#ifndef WORDLE_FOUNDATION_MEMORY_H
#define WORDLE_FOUNDATION_MEMORY_H
#include <experimental/propagate_const>
#include <memory>

namespace wordle::foundation {

template <typename Type>
using ConstAware = std::experimental::propagate_const<Type>;

template <typename Type>
using StdUniquePtr = std::unique_ptr<Type>;

template <typename Type>
using StdSharedPtr = std::shared_ptr<Type>;

template <typename Type>
using StdWeakPtr = std::weak_ptr<Type>;

template <typename Type>
using ConstAwareStdUniquePtr = ConstAware<StdUniquePtr<Type>>;

template <typename Type>
using ConstAwareStdSharedPtr = ConstAware<StdSharedPtr<Type>>;

template <typename Type>
using ConstAwareStdWeakPtr = ConstAware<StdWeakPtr<Type>>;
}  // namespace wordle::foundation

#endif
