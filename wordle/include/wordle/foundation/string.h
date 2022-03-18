#ifndef WORDLE_FOUNDATION_STRING_H
#define WORDLE_FOUNDATION_STRING_H

#include <string>

namespace wordle::foundation {
#if UNICODE
using String = std::wstring;
using StringView = std::wstring_view;
#else
using String = std::string;
using StringView = std::string_view;
#endif
}  // namespace wordle::foundation

#endif
