#ifndef WORDLE_FOUNDATION_JSON_JSONSERIALIZER_H
#define WORDLE_FOUNDATION_JSON_JSONSERIALIZER_H

#include <folly/SingletonThreadLocal.h>
#include <wordle/foundation/json/types.h>
#include <wordle/prelude/prelude.h>

#include <memory>

namespace wordle::foundation::json {
class WORDLE_PUBLIC_API JsonSerializer final {
 public:
  [[nodiscard]] static auto instance() -> JsonSerializer&;

 private:
  JsonSerializer() = default;
  friend class folly::detail::DefaultMake<JsonSerializer>;
};
}  // namespace wordle::foundation::json

#endif
