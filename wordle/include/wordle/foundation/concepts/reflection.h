#ifndef WORDLE_FOUNDATION_CONCEPTS_REFLECTION_H
#define WORDLE_FOUNDATION_CONCEPTS_REFLECTION_H

#include <concepts>

namespace wordle::foundation::concepts {
template <class A, class B>
concept SameAs = std::same_as<A, B>;

template <class A, class B>
concept CommonReferenceWith = std::common_reference_with<A, B>;

template <class MaybeEnum>
concept Enum = std::is_enum_v<MaybeEnum>;

template <class MaybeErrorCode>
concept ErrorCode = std::is_error_code_enum_v<MaybeErrorCode>;

template <class MaybeUnion>
concept Union = std::is_union_v<MaybeUnion>;

template <class MaybeClass>
concept Class = std::is_class_v<MaybeClass>;

template <class MaybeClassOrEnum>
concept ClassOrEnum = Class<MaybeClassOrEnum> || Union<MaybeClassOrEnum> ||
    Enum<MaybeClassOrEnum>;

}  // namespace wordle::foundation::concepts

#endif
