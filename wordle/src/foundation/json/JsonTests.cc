#include <gtest/gtest.h>
#include <wordle/foundation/foundation.h>

#include "fixtures/DeserializableObject.h"

namespace wordle::foundation::json::tests {

TEST(Json, deserialize) {
  constexpr auto data = R"({"id": 1})"sv;
  auto result = json::deserialize<fixtures::DeserializableObject>(data);
  ASSERT_EQ(result.error(), JsonErrorCode::SUCCESS);
  auto value = result.value();
  ASSERT_NE(value, nullptr);
  ASSERT_EQ(value->id(), 1);
}

}  // namespace wordle::foundation::json::tests
