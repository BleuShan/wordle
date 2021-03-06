#include <wordle/foundation/filesystem/DirectoryContents.h>
#include <wordle/foundation/filesystem/providers/details/PhysicalFileProviderContext.h>

using wordle::foundation::filesystem::providers::details::
    PhysicalFileProviderContext;
namespace fs = std::filesystem;

PhysicalFileProviderContext::PhysicalFileProviderContext(
    const FilePath& path) noexcept
    : path_{path} {}

auto PhysicalFileProviderContext::getDirectoryContents() const
    -> DirectoryContents::SharedPtr {
  return DirectoryContents::create(path_);
}

auto PhysicalFileProviderContext::path() const -> const FilePath {
  return path_;
}
