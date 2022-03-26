#ifndef WORDLE_FOUNDATION_FILESYSTEM_PROVIDERS_FILEPROVIDER_H
#define WORDLE_FOUNDATION_FILESYSTEM_PROVIDERS_FILEPROVIDER_H

#include <wordle/prelude/prelude.h>

#include <wordle/foundation/concepts/concepts.h>
#include <wordle/foundation/memory.h>

#include <wordle/foundation/filesystem/DirectoryContents.h>

#include <wordle/foundation/filesystem/providers/details/FileProviderContext.h>

#include <folly/Singleton.h>
#include <functional>

namespace wordle::foundation::filesystem::providers {
class WORDLE_PUBLIC_API FileProvider final
    : public std::enable_shared_from_this<FileProvider> {
 public:
  using SharedPtr = StdSharedPtr<FileProvider>;
  using WeakPtr = StdWeakPtr<FileProvider>;

  FileProvider() = delete;
  FileProvider operator=(const FileProvider&) = delete;

  static auto currentDirectory() -> SharedPtr;
  auto getDirectoryContents() const { return context_->getDirectoryContents(); }
  auto path() const { return context_->path(); }

  template <concepts::DerivedFrom<details::FileProviderContext> Context,
            typename Tag = folly::detail::DefaultTag, typename VaultTag = Tag,
            typename... Args>
  static auto singleton(Args&&... args) {
    auto context = new Context{std::forward<Args>(args)...};
    return folly::Singleton<FileProvider, Tag, VaultTag>{
        [context]() { return new FileProvider{context}; }};
  }

 private:
  explicit FileProvider(details::FileProviderContext* context);
  StdUniquePtr<details::FileProviderContext> context_;
};

}  // namespace wordle::foundation::filesystem::providers

#endif
