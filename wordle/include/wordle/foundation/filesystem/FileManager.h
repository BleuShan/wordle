#ifndef WORDLE_FOUNDATION_FILESYSTEM_FILEMANAGER_H
#define WORDLE_FOUNDATION_FILESYSTEM_FILEMANAGER_H

#include <wordle/foundation/mixins.h>
#include <wordle/prelude.h>

namespace wordle::foundation::filesystem {
class WORDLE_PUBLIC_API FileManager : public mixins::Singleton<FileManager> {
 private:
  /* data */
 public:
  FileManager(/* args */);
  ~FileManager();
};

}  // namespace wordle::foundation::filesystem

#endif
