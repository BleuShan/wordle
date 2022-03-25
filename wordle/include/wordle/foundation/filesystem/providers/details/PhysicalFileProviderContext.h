#ifndef WORDLE_FOUNDATION_FILESYSTEM_PROVIDERS_DETAILS_PHYSICALFILEPROVIDERCONTEXT_H
#define WORDLE_FOUNDATION_FILESYSTEM_PROVIDERS_DETAILS_PHYSICALFILEPROVIDERCONTEXT_H
#include <wordle/prelude/prelude.h>

#include <wordle/foundation/memory.h>

#include <wordle/foundation/filesystem/types.h>

#include <wordle/foundation/filesystem/providers/details/FileProviderContext.h>

namespace wordle::foundation::filesystem::providers::details {
class WORDLE_PUBLIC_API PhysicalFileProviderContext
    : public FileProviderContext {
 public:
  static auto create(const FilePath& path) -> StdUniquePtr<FileProviderContext>;
  virtual auto getDirectoryContents() const
      -> DirectoryContents::SharedPtr override;
  virtual auto path() const -> const FilePath override;

 private:
  PhysicalFileProviderContext(const FilePath& path) noexcept;
  FilePath path_;
};
}  // namespace wordle::foundation::filesystem::providers::details
#endif
