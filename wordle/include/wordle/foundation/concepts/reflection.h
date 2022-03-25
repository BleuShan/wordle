#ifndef WORDLE_FOUNDATION_CONCEPTS_REFLECTION_H
#define WORDLE_FOUNDATION_CONCEPTS_REFLECTION_H

#include <concepts>
#include <system_error>

namespace wordle::foundation::concepts {
template <typename Derived, typename Base>
concept DerivedFrom = std::derived_from<Derived, Base>;

template <typename A, typename B>
concept SameAs = std::same_as<A, B>;

template <typename A, typename B>
concept CommonReferenceWith = std::common_reference_with<A, B>;

template <typename Type>
concept Enum = std::is_enum_v<Type>;

template <typename Type>
concept ScopedEnum = std::is_enum_v<Type>;

template <typename Type>
concept ErrorCode = std::is_error_code_enum_v<Type>;

template <typename Type>
concept Union = std::is_union_v<Type>;

template <typename Type>
concept Class = std::is_class_v<Type>;

template <typename Type>
concept ClassOrEnum = Class<Type> || Union<Type> || Enum<Type>;

template <typename Type>
concept Integral = std::integral<Type>;

template <typename Type>
concept SignedIntegral = std::signed_integral<Type>;

template <typename Type>
concept UnsignedIntegral = std::unsigned_integral<Type>;

template <typename Type>
concept FloatingPoint = std::floating_point<Type>;

}  // namespace wordle::foundation::concepts

#endif
