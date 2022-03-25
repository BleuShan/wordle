#include <wordle/foundation/filesystem/DirectoryContents.h>

using wordle::foundation::filesystem::DirectoryContents;
namespace fs = std::filesystem;

DirectoryContents::DirectoryContents(const FilePath& path) noexcept
    : path_{path} {}

auto DirectoryContents::create(const FilePath& path) -> SharedPtr {
  if (!fs::is_directory(path)) {
    return nullptr;
  }
  return SharedPtr{new DirectoryContents{path}};
}
