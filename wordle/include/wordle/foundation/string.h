#ifndef WORDLE_FOUNDATION_STRING_H
#define WORDLE_FOUNDATION_STRING_H

#include <folly/FBString.h>
#include <folly/FixedString.h>
#include <folly/String.h>

#include <simdjson.h>

using namespace std::literals;

namespace wordle::foundation {
template <std::size_t N>
using FixedString = folly::FixedString<N>;
using String = folly::fbstring;
using StdString = std::string;
using StringView = std::string_view;
using PaddedString = simdjson::padded_string;
using PaddedStringView = simdjson::padded_string_view;

}  // namespace wordle::foundation

#endif
