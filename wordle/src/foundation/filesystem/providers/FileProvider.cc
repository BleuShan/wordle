#include <wordle/foundation/filesystem/providers/FileProvider.h>
#include <wordle/foundation/filesystem/providers/details/PhysicalFileProviderContext.h>

using wordle::foundation::filesystem::providers::FileProvider;
using wordle::foundation::filesystem::providers::details::
    PhysicalFileProviderContext;

static auto DefaultFileProvider =
    FileProvider::singleton<PhysicalFileProviderContext>(
        std::filesystem::current_path());

FileProvider::FileProvider(details::FileProviderContext* context)
    : context_{context} {}

auto FileProvider::currentDirectory() -> FileProvider::SharedPtr {
  return DefaultFileProvider.try_get();
}
