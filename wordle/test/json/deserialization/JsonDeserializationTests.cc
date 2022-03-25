#include <gtest/gtest.h>
#include <wordle/foundation/foundation.h>

#include "fixtures/DeserializableObject.h"

namespace wordle::foundation::json::deserialization::tests {

TEST(Json, deserialize) {
  constexpr const auto data = R"({"id": 1})"sv;
  auto basic = json::deserialize<fixtures::DeserializableObject>(data);
  ASSERT_NE(basic, nullptr);
  ASSERT_EQ(basic->id(), 1);

  constexpr const auto stringIdData = R"({"id": "2"})"sv;
  auto stringId =
      json::deserialize<fixtures::DeserializableObject>(stringIdData);
  ASSERT_NE(stringId, nullptr);
  ASSERT_NE(basic, stringId);
  ASSERT_EQ(stringId->id(), 2);
}

}  // namespace wordle::foundation::json::deserialization::tests
