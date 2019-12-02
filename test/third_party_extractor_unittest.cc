#include "brave/vendor/brave_performance_predictor/src/third_party_extractor.h"

#include "testing/gtest/include/gtest/gtest.h"

namespace brave_savings {
	const std::string test_mapping = R"([{"name":"Google Analytics","company":"Google","homepage":"https://www.google.com/analytics/analytics/","categories":["analytics"],"domains":["www.google-analytics.com","ssl.google-analytics.com","google-analytics.com","urchin.com"]},{"name":"Facebook","homepage":"https://www.facebook.com","categories":["social"],"domains":["www.facebook.com","connect.facebook.net","staticxx.facebook.com","static.xx.fbcdn.net","m.facebook.com","atlassbx.com","fbcdn-photos-e-a.akamaihd.net","23.62.3.183","akamai.net","akamaiedge.net","akamaitechnologies.com","akamaitechnologies.fr","akamaized.net","edgefcs.net","edgekey.net","edgesuite.net","srip.net","cquotient.com","demandware.net","platform-lookaside.fbsbx.com"]}])";
}

class ThirdPartyExtractorTest : public ::testing::Test {
 protected:
  ThirdPartyExtractorTest() {
    // You can do set-up work for each test here
  }

  ~ThirdPartyExtractorTest() override {
    // You can do clean-up work that doesn't throw exceptions here
  }

  // If the constructor and destructor are not enough for setting up and
  // cleaning up each test, you can use the following methods

  void SetUp() override {
    // Code here will be called immediately after the constructor (right before
    // each test)
  }

  void TearDown() override {
    // Code here will be called immediately after each test (right before the
    // destructor)
  }

};

TEST_F(ThirdPartyExtractorTest, ParsesJSONTest) {
  brave_savings::ThirdPartyExtractor extractor(brave_savings::test_mapping);
  {
  	auto entity = extractor.get_entity("https://google-analytics.com/");
    EXPECT_TRUE(entity.has_value());
    EXPECT_EQ(entity.value(), "Google Analytics");
  }

  {
  	auto entity = extractor.get_entity("google-analytics.com");
    EXPECT_TRUE(entity.has_value());
    EXPECT_EQ(entity.value(), "Google Analytics");
  }

  {
    auto entity = extractor.get_entity("https://test.m.facebook.com");
    EXPECT_TRUE(entity.has_value());
    EXPECT_EQ(entity.value(), "Facebook");
  }
}