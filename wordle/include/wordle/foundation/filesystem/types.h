#ifndef WORDLE_FOUNDATION_FILESYSTEM_TYPES_H
#define WORDLE_FOUNDATION_FILESYSTEM_TYPES_H

#include <wordle/foundation/filesystem/providers/types.h>
#include <filesystem>

namespace wordle::foundation::filesystem {
using FilePath = std::filesystem::path;

class DirectoryContents;
class FileInfo;
}  // namespace wordle::foundation::filesystem

#endif
