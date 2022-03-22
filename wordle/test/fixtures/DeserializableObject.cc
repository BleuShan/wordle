#include "DeserializableObject.h"

#include <wordle/foundation/foundation.h>

namespace wordle::foundation::json::tests::fixtures {

auto DeserializableObject::JsonDeserializer::deserialize(
    JsonPaddedStringView rawJson) -> SharedPtr {
  auto document = parser_->iterate(rawJson);
  JsonObject root = document.get_object();
  SharedPtr instance{nullptr};
  for (auto&& field : root) {
    StringView fieldName = field.unescaped_key();
    if (!fieldNames_.contains(fieldName)) {
      throw JsonError{JsonErrorCode::NO_SUCH_FIELD};
    }
    auto value = field.value();

    if (fieldName == "id") {
      uint64_t id;
      auto error = value.get_uint64().get(id);
      if (error == JsonErrorCode::INCORRECT_TYPE) {
        error = value.get_uint64_in_string().get(id);
      }

      if (error) {
        throw JsonError{error};
      }

      if (instance == nullptr) {
        instance = SharedPtr{new DeserializableObject()};
      }

      instance->id_ = id;
    }
  }

  return instance;
}
}  // namespace wordle::foundation::json::tests::fixtures
