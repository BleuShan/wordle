#ifndef WORDLE_FOUNDATION_JSON_FIXTURES_DESERIALIZABLEOBJECT_H
#define WORDLE_FOUNDATION_JSON_FIXTURES_DESERIALIZABLEOBJECT_H

#include <wordle/foundation/foundation.h>

#include <memory>

namespace wordle::foundation::json::tests::fixtures {
class DeserializableObject final
    : public std::enable_shared_from_this<DeserializableObject> {
 public:
  using SharedPtr = std::shared_ptr<DeserializableObject>;
  using WeakPtr = SharedPtr::weak_type;

  struct JsonDeserializer final {
    using Output = DeserializableObject;
    JsonDeserializer(JsonPaddedStringView jsonPayload)
        : rawJson_{jsonPayload} {}

    auto operator()() {
      JsonDocument document = parser_->iterate(rawJson_);
      auto root = document.get_object();
      auto error = root.error();
      SharedPtr instance = nullptr;
      if (error == JsonErrorCode::SUCCESS) {
        for (auto&& field : root) {
          auto fieldKey = field.unescaped_key();
          auto fieldValue = field.value();
          error = fieldKey.error();

          if (error != JsonErrorCode::SUCCESS) {
            break;
          }

          MemberNames key = evaluate(fieldKey.value());
          switch (key) {
            case MemberNames::id: {
              error = fieldValue.error();
              if (!error) {
                if (instance == nullptr) {
                  instance = SharedPtr(new DeserializableObject());
                }
                instance->id_ = fieldValue.get_uint64().take_value();
              }
              break;
            }
            default:
              error = JsonErrorCode::NO_SUCH_FIELD;
              instance = nullptr;
              break;
          }

          if (error != JsonErrorCode::SUCCESS) {
            break;
          }
        }
      }

      return JsonResult<SharedPtr>(std::move(instance), error);
    }

   private:
    std::unique_ptr<JsonParser> parser_ = std::make_unique<JsonParser>();
    JsonPaddedStringView rawJson_;

    enum class MemberNames { INVALID = 0, id };

    constexpr MemberNames evaluate(
        foundation::StringView value) const noexcept {
      if (value.compare("id") == 0) {
        return MemberNames::id;
      }
      return MemberNames::INVALID;
    }
  };

  auto id() const noexcept { return id_; }

 private:
  uint64_t id_;
  DeserializableObject() = default;
};
}  // namespace wordle::foundation::json::tests::fixtures
#endif
