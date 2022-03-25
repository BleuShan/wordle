#ifndef WORDLE_FOUNDATION_JSON_FIXTURES_DESERIALIZABLEOBJECT_H
#define WORDLE_FOUNDATION_JSON_FIXTURES_DESERIALIZABLEOBJECT_H

#include <wordle/foundation/foundation.h>

#include <memory>
#include <unordered_set>

namespace wordle::foundation::json::tests::fixtures {

class DeserializableObject final
    : public std::enable_shared_from_this<DeserializableObject> {
 public:
  using SharedPtr = std::shared_ptr<DeserializableObject>;
  using WeakPtr = SharedPtr::weak_type;

  constexpr auto id() const noexcept { return id_; }

  class JsonDeserializer final {
   public:
    auto deserialize(JsonPaddedStringView rawJson) -> SharedPtr;

   private:
    std::unique_ptr<JsonParser> parser_ = std::make_unique<JsonParser>();
    const std::unordered_set<StringView> fieldNames_ = {"id"};
  };

 private:
  uint64_t id_;
  DeserializableObject() = default;
};

}  // namespace wordle::foundation::json::tests::fixtures
#endif
