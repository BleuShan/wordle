#include <folly/Singleton.h>
#include <wordle/foundation/filesystem/filesystem.h>

using wordle::foundation::filesystem::FileProvider;

static auto DefaultFileProvider = folly::Singleton<FileProvider>{
    wordle::foundation::filesystem::createDefaultFileProvider};

namespace wordle::foundation::filesystem {
FileProvider::FileProvider(const FilePath& path) : path_{path} {
  if (std::filesystem::is_directory(path_) && path_.has_parent_path()) {
    path_ = path_.parent_path();
  }
}

auto FileProvider::instance() -> FileProvider::SharedPtr {
  return DefaultFileProvider.try_get();
}

auto createDefaultFileProvider() -> FileProvider* {
  return new FileProvider(std::filesystem::current_path());
}
}