#ifndef WORDLE_FOUNDATION_FILESYSTEM_FILEPROVIDER_H
#define WORDLE_FOUNDATION_FILESYSTEM_FILEPROVIDER_H

#include <folly/Singleton.h>
#include <wordle/prelude/prelude.h>

#include <memory>

namespace wordle::foundation::filesystem {
class WORDLE_PUBLIC_API FileProvider final
    : public std::enable_shared_from_this<FileProvider> {
 public:
  using SharedPtr = std::shared_ptr<FileProvider>;
  using WeakPtr = std::weak_ptr<FileProvider>;

  static auto instance() -> SharedPtr;

 private:
  FileProvider() = default;
  friend class folly::Singleton<FileProvider>;
};

}  // namespace wordle::foundation::filesystem

#endif
