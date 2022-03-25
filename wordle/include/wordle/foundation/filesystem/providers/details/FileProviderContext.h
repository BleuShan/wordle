#ifndef WORDLE_FOUNDATION_FILESYSTEM_PROVIDERS_DETAILS_FILEPROVIDERCONTEXT_H
#define WORDLE_FOUNDATION_FILESYSTEM_PROVIDERS_DETAILS_FILEPROVIDERCONTEXT_H

#include <wordle/prelude/prelude.h>

#include <wordle/foundation/memory.h>

#include <wordle/foundation/filesystem/types.h>

namespace wordle::foundation::filesystem::providers::details {
class WORDLE_PUBLIC_API FileProviderContext {
 public:
  virtual auto getDirectoryContents() const -> DirectoryContents::SharedPtr = 0;
  virtual auto path() const -> const FilePath = 0;

 protected:
  FileProviderContext() = default;
};
}  // namespace wordle::foundation::filesystem::providers::details
#endif
