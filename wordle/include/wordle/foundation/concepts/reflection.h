#ifndef WORDLE_FOUNDATION_CONCEPTS_REFLECTION_H
#define WORDLE_FOUNDATION_CONCEPTS_REFLECTION_H

#include <concepts>
#include <system_error>

namespace wordle::foundation::concepts {
template <class A, class B>
concept SameAs = std::same_as<A, B>;

template <class A, class B>
concept CommonReferenceWith = std::common_reference_with<A, B>;

template <class Type>
concept Enum = std::is_enum_v<Type>;

template <class Type>
concept ScopedEnum = std::is_enum_v<Type>;

template <class Type>
concept ErrorCode = std::is_error_code_enum_v<Type>;

template <class Type>
concept Union = std::is_union_v<Type>;

template <class Type>
concept Class = std::is_class_v<Type>;

template <class Type>
concept ClassOrEnum = Class<Type> || Union<Type> || Enum<Type>;

template <class Type>
concept Integral = std::integral<Type>;

template <class Type>
concept SignedIntegral = std::signed_integral<Type>;

template <class Type>
concept UnsignedIntegral = std::unsigned_integral<Type>;

template <class Type>
concept FloatingPoint = std::floating_point<Type>;

}  // namespace wordle::foundation::concepts

#endif
