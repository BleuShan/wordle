#ifndef WORDLE_FOUNDATION_FILESYSTEM_FILEPROVIDER_H
#define WORDLE_FOUNDATION_FILESYSTEM_FILEPROVIDER_H

#include <wordle/foundation/filesystem/types.h>
#include <wordle/prelude/prelude.h>

#include <memory>

namespace wordle::foundation::filesystem {
class WORDLE_PUBLIC_API FileProvider final
    : public std::enable_shared_from_this<FileProvider> {
 public:
  using SharedPtr = std::shared_ptr<FileProvider>;
  using WeakPtr = std::weak_ptr<FileProvider>;

  static auto instance() -> SharedPtr;

  template <typename... Args>
  static auto create(Args&&... args) {
    return SharedPtr{new FileProvider{std::forward<Args>(args)...}};
  }
 private:
  FileProvider(const FilePath& path);

  friend auto createDefaultFileProvider() -> FileProvider*;
  FilePath path_;
};

WORDLE_PRIVATE_API auto createDefaultFileProvider() -> FileProvider*;

}  // namespace wordle::foundation::filesystem

#endif
