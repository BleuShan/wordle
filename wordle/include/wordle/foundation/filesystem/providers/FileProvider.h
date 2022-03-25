#ifndef WORDLE_FOUNDATION_FILESYSTEM_PROVIDERS_FILEPROVIDER_H
#define WORDLE_FOUNDATION_FILESYSTEM_PROVIDERS_FILEPROVIDER_H

#include <wordle/prelude/prelude.h>

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
  class Builder;

  FileProvider() = delete;
  FileProvider operator=(const FileProvider &) = delete;

  static auto currentDirectory() -> SharedPtr;

  auto getDirectoryContents() const { return context_->getDirectoryContents(); }

  auto path() const { return context_->path(); }

 private:
  explicit FileProvider(const Builder &builder);
  ConstAwareStdUniquePtr<details::FileProviderContext> context_;
};

class FileProvider::Builder : public std::enable_shared_from_this<Builder> {
 public:
  using SharedPtr = StdSharedPtr<Builder>;
  using WeakPtr = StdWeakPtr<Builder>;
  using ConfigureFn = std::function<void(SharedPtr)>;
  using ContextFactoryFn =
      std::function<StdUniquePtr<details::FileProviderContext>()>;
  using TeardownFn = std::function<void(FileProvider *)>;

  Builder(const Builder &) = delete;
  Builder operator=(const Builder &) = delete;

  template <typename Tag = folly::detail::DefaultTag,
            typename VaultTag = folly::detail::DefaultTag>
  static auto &&create(ConfigureFn configure) {
    using BuilderHolder = folly::Singleton<Builder, Tag, VaultTag>;
    BuilderHolder holder{[]() { return new Builder(); }};

    auto singleton = folly::Singleton<FileProvider, Tag, VaultTag>{
        [configure, &holder]() -> FileProvider * {
          auto builder = holder.try_get();
          if (builder == nullptr) {
            return nullptr;
          }
          configure(builder);
          return builder->build();
        },
        [&holder](auto provider) {
          auto builder = holder.try_get();
          if (builder == nullptr || provider == nullptr) return;
          auto impl = builder->teardownImpl_;
          if (impl == nullptr) return;
          impl(provider);
        }};
    return std::move(singleton);
  }

  auto context(ContextFactoryFn fn) {
    contextImpl_ = fn;
    return shared_from_this();
  }

  auto context() const -> StdUniquePtr<details::FileProviderContext> {
    if (contextImpl_ == nullptr) {
      return nullptr;
    }

    return contextImpl_();
  }

  const auto &teardown() const { return teardownImpl_; }
  auto teardown(TeardownFn fn) {
    teardownImpl_ = fn;
    return shared_from_this();
  }

 private:
  Builder() = default;
  auto &&build() const { return std::move(new FileProvider(*this)); }
  ContextFactoryFn contextImpl_ = nullptr;
  TeardownFn teardownImpl_ = nullptr;
};

}  // namespace wordle::foundation::filesystem::providers

#endif
