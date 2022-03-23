#include <folly/Singleton.h>
#include <wordle/foundation/filesystem/filesystem.h>

using wordle::foundation::filesystem::FileProvider;

const folly::Singleton<FileProvider> kFileManager;

namespace wordle::foundation::filesystem {
auto FileProvider::instance() -> FileProvider::SharedPtr {
  return kFileManager.try_get();
}
}
