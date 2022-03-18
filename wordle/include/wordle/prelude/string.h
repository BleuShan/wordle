#ifndef WORDLE_PRELUDE_STRING_H
#define WORDLE_PRELUDE_STRING_H

#include <string>

namespace wordle {
#if UNICODE
using String = std::wstring;
using StringView = std::wstring_view;
#else
using String = std::string;
using StringView = std::string_view;
#endif
}  // namespace wordle

#endif
