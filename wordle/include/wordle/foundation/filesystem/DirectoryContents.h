#ifndef WORDLE_FOUNDATION_FILESYSTEM_DIRECTORYCONTENTS_H
#define WORDLE_FOUNDATION_FILESYSTEM_DIRECTORYCONTENTS_H

#include <wordle/prelude/prelude.h>

#include <wordle/foundation/memory.h>

#include <wordle/foundation/filesystem/types.h>

namespace wordle::foundation::filesystem {
class WORDLE_PUBLIC_API DirectoryContents final
    : public std::enable_shared_from_this<DirectoryContents> {
 public:
  using SharedPtr = StdSharedPtr<DirectoryContents>;
  using WeakPtr = StdWeakPtr<DirectoryContents>;

  static auto create(const FilePath& path) -> SharedPtr;

 private:
  DirectoryContents(const FilePath& path) noexcept;
  FilePath path_;
};

}  // namespace wordle::foundation::filesystem

#endif
