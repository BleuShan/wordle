#ifndef WORDLE_FOUNDATION_FILESYSTEM_FILEMANAGER_H
#define WORDLE_FOUNDATION_FILESYSTEM_FILEMANAGER_H

#include <folly/Singleton.h>
#include <wordle/prelude/prelude.h>

#include <memory>

namespace wordle::foundation::filesystem {
class WORDLE_PUBLIC_API FileManager final
    : public std::enable_shared_from_this<FileManager> {
 public:
  using SharedPtr = std::shared_ptr<FileManager>;
  using WeakPtr = std::weak_ptr<FileManager>;

  static auto instance() -> SharedPtr;

 private:
  FileManager() = default;
  friend class folly::Singleton<FileManager>;
};

}  // namespace wordle::foundation::filesystem

#endif
