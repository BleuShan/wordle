#ifndef WORDLE_FOUNDATION_STRING_H
#define WORDLE_FOUNDATION_STRING_H

#include <folly/FBString.h>
#include <folly/FixedString.h>
#include <folly/String.h>
using namespace std::literals;

namespace wordle::foundation {
template <std::size_t N>
using FixedString = folly::FixedString<N>;
using String = folly::fbstring;
using StdString = std::string;
using StringView = std::string_view;

}  // namespace wordle::foundation

#endif
