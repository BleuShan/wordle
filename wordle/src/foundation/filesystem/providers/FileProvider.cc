#include <wordle/foundation/filesystem/providers/FileProvider.h>
#include <wordle/foundation/filesystem/providers/details/PhysicalFileProviderContext.h>

using wordle::foundation::filesystem::providers::FileProvider;
using wordle::foundation::filesystem::providers::details::
    PhysicalFileProviderContext;

static auto DefaultFileProvider =
    FileProvider::Builder::create([](auto builder) {
      builder
          ->context([]() {
            return PhysicalFileProviderContext::create(
                std::filesystem::current_path());
          })
          ->teardown([](auto provider) { printf("shutting down"); });
    });

FileProvider::FileProvider(const FileProvider::Builder& builder)
    : context_{builder.context()} {}

auto FileProvider::currentDirectory() -> FileProvider::SharedPtr {
  return DefaultFileProvider.try_get();
}
