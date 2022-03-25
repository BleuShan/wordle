#include <wordle/foundation/filesystem/DirectoryContents.h>
#include <wordle/foundation/filesystem/providers/details/PhysicalFileProviderContext.h>

using wordle::foundation::filesystem::providers::details::
    PhysicalFileProviderContext;
namespace fs = std::filesystem;

PhysicalFileProviderContext::PhysicalFileProviderContext(
    const FilePath& path) noexcept
    : path_{path} {}

auto PhysicalFileProviderContext::create(const FilePath& path)
    -> StdUniquePtr<FileProviderContext> {
  if (!fs::is_directory(path)) {
    return nullptr;
  }
  return StdUniquePtr<FileProviderContext>{
      new PhysicalFileProviderContext(path)};
}

auto PhysicalFileProviderContext::getDirectoryContents() const
    -> DirectoryContents::SharedPtr {
  return DirectoryContents::create(path_);
}

auto PhysicalFileProviderContext::path() const -> const FilePath {
  return path_;
}
