#include <folly/Singleton.h>
#include <wordle/foundation/filesystem/FileManager.h>

using wordle::foundation::filesystem::FileManager;

const folly::Singleton<FileManager> kFileManager;

auto FileManager::instance() -> FileManager::SharedPtr {
  return kFileManager.try_get();
}
