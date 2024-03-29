#include <fstream>
#include <streambuf>

#include "brave/vendor/brave_perf_predictor/src/predictor.h"

#include "testing/gtest/include/gtest/gtest.h"
#include "base/files/file_path.h"

namespace brave_perf_predictor {

class BraveSavingsPredictorTest : public ::testing::Test {
 protected:
  BraveSavingsPredictorTest() {
    // You can do set-up work for each test here
  }

  ~BraveSavingsPredictorTest() override {
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

TEST_F(BraveSavingsPredictorTest, FeatureArrayGetsPrediction) {
  std::array<double, feature_count> features{};
  double result = predict(features);
  EXPECT_TRUE(result != 0);
}

TEST_F(BraveSavingsPredictorTest, HandlesSpecificVectorExample) {
  // This test needs to be updated for any change in the model
  std::array<double, feature_count> sample = {
    20, 129, 225, 225, 142,
    925, 5, 34662, 3, 317818, 9, 1702888,
    0, 0, 1, 324, 32, 238315, 9,
    90131, 54, 2367498, 59, 2384138,
    0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0       
  };

  double result = brave_perf_predictor::predict(sample);
  EXPECT_EQ((int)result, 794393);
}

TEST_F(BraveSavingsPredictorTest, HandlesEmptyFeatureset) {
  std::unordered_map<std::string, double> features{};
  double result = predict(features);
  std::array<double, feature_count> features_array{};
  double array_result = predict(features_array);
  EXPECT_EQ(result, array_result);
}

TEST_F(BraveSavingsPredictorTest, HandlesCompleteFeatureset) {
  std::unordered_map<std::string, double> features;
  for (unsigned int i = 0; i < feature_count; i++) {
    features[feature_sequence[i]] = 0;
  }
  double result = predict(features);
  std::array<double, feature_count> array_features{};
  double array_result = predict(array_features);
  EXPECT_EQ(result, array_result);
}

TEST_F(BraveSavingsPredictorTest, HandesSpecificFeaturemapExample) {
  // This test needs to be updated for any change in the model
  std::unordered_map<std::string, double> featuremap = {
    { "thirdParties.Google Analytics.blocked", 0 },
    { "thirdParties.Facebook.blocked", 1 },
    { "thirdParties.Google CDN.blocked", 0 },
    { "thirdParties.Twitter.blocked", 0 },
    { "thirdParties.Other Google APIs/SDKs.blocked", 0 },
    { "thirdParties.Scorecard Research.blocked", 0 },
    { "thirdParties.Sortable.blocked", 0 },
    { "thirdParties.Google/Doubleclick Ads.blocked", 0 },
    { "thirdParties.Adobe Tag Manager.blocked", 0 },
    { "thirdParties.Google Tag Manager.blocked", 1 },
    { "thirdParties.Chartbeat.blocked", 0 },
    { "thirdParties.Amazon Ads.blocked", 0 },
    { "thirdParties.Salesforce.blocked", 0 },
    { "thirdParties.Adobe Test & Target.blocked", 0 },
    { "thirdParties.YouTube.blocked", 1 },
    { "thirdParties.Outbrain.blocked", 0 },
    { "thirdParties.Tumblr.blocked", 0 },
    { "thirdParties.WordPress.blocked", 0 },
    { "thirdParties.Bing Ads.blocked", 0 },
    { "thirdParties.New Relic.blocked", 0 },
    { "thirdParties.JuicyAds.blocked", 0 },
    { "thirdParties.Audience 360.blocked", 0 },
    { "thirdParties.Revcontent.blocked", 0 },
    { "thirdParties.Pubmatic.blocked", 0 },
    { "thirdParties.AppNexus.blocked", 0 },
    { "thirdParties.SpotXchange.blocked", 0 },
    { "thirdParties.AOL / Oath / Verizon Media.blocked", 0 },
    { "thirdParties.Amazon Web Services.blocked", 0 },
    { "thirdParties.LoopMe.blocked", 0 },
    { "thirdParties.Quantcast.blocked", 0 },
    { "thirdParties.Click4Assistance.blocked", 0 },
    { "thirdParties.Hotjar.blocked", 0 },
    { "thirdParties.Snapchat.blocked", 1 },
    { "thirdParties.jQuery CDN.blocked", 0 },
    { "thirdParties.Segment.blocked", 0 },
    { "thirdParties.Usabilla.blocked", 0 },
    { "thirdParties.Nativo.blocked", 0 },
    { "thirdParties.Sharethrough.blocked", 0 },
    { "thirdParties.Twitter Online Conversion Tracking.blocked", 0 },
    { "thirdParties.BounceX.blocked", 0 },
    { "thirdParties.Integral Ad Science.blocked", 0 },
    { "thirdParties.Rubicon Project.blocked", 0 },
    { "thirdParties.Index Exchange.blocked", 0 },
    { "thirdParties.Sentry.blocked", 0 },
    { "thirdParties.Cloudflare CDN.blocked", 0 },
    { "thirdParties.VigLink.blocked", 0 },
    { "thirdParties.Optimizely.blocked", 0 },
    { "thirdParties.Ensighten.blocked", 0 },
    { "thirdParties.Criteo.blocked", 0 },
    { "thirdParties.Nielsen NetRatings SiteCensus.blocked", 0 },
    { "thirdParties.Cookie-Script.com.blocked", 0 },
    { "thirdParties.Rackspace.blocked", 0 },
    { "thirdParties.Adobe TypeKit.blocked", 0 },
    { "thirdParties.Stripe.blocked", 0 },
    { "thirdParties.Trust Pilot.blocked", 0 },
    { "thirdParties.Polyfill service.blocked", 0 },
    { "thirdParties.Affiliate Window.blocked", 0 },
    { "thirdParties.FontAwesome CDN.blocked", 0 },
    { "thirdParties.Bootstrap CDN.blocked", 0 },
    { "thirdParties.Auto Link Maker.blocked", 0 },
    { "thirdParties.Embedly.blocked", 0 },
    { "thirdParties.JSDelivr CDN.blocked", 0 },
    { "thirdParties.OneSignal.blocked", 0 },
    { "thirdParties.The Trade Desk.blocked", 0 },
    { "thirdParties.Instagram.blocked", 1 },
    { "thirdParties.PayPal.blocked", 0 },
    { "thirdParties.Taboola.blocked", 0 },
    { "thirdParties.Opentag.blocked", 0 },
    { "thirdParties.Brightcove.blocked", 0 },
    { "thirdParties.VWO.blocked", 0 },
    { "thirdParties.Rambler.blocked", 0 },
    { "thirdParties.Media Math.blocked", 0 },
    { "thirdParties.Google Maps.blocked", 0 },
    { "thirdParties.Unpkg.blocked", 0 },
    { "thirdParties.Yandex Share.blocked", 0 },
    { "thirdParties.Yandex Metrica.blocked", 0 },
    { "thirdParties.Yandex CDN.blocked", 0 },
    { "thirdParties.Amplitude Mobile Analytics.blocked", 0 },
    { "thirdParties.Yahoo!.blocked", 0 },
    { "thirdParties.Yandex Ads.blocked", 0 },
    { "thirdParties.piano.blocked", 0 },
    { "thirdParties.Moat.blocked", 0 },
    { "thirdParties.Parse.ly.blocked", 0 },
    { "thirdParties.Unruly Media.blocked", 0 },
    { "thirdParties.Skimbit.blocked", 0 },
    { "thirdParties.ZenDesk.blocked", 0 },
    { "thirdParties.Silverpop.blocked", 0 },
    { "thirdParties.AddThis.blocked", 1 },
    { "thirdParties.Polldaddy.blocked", 0 },
    { "thirdParties.Dailymotion.blocked", 0 },
    { "thirdParties.Disqus.blocked", 0 },
    { "thirdParties.Alexa.blocked", 0 },
    { "thirdParties.Mailchimp.blocked", 0 },
    { "thirdParties.Tealium.blocked", 0 },
    { "thirdParties.LiveChat.blocked", 0 },
    { "thirdParties.DemandBase.blocked", 0 },
    { "thirdParties.Tencent.blocked", 0 },
    { "thirdParties.Oracle Recommendations On Demand.blocked", 0 },
    { "thirdParties.Mixpanel.blocked", 0 },
    { "thirdParties.PerimeterX Bot Defender.blocked", 0 },
    { "thirdParties.Evidon.blocked", 0 },
    { "thirdParties.Media.net.blocked", 0 },
    { "thirdParties.Ghostery Enterprise.blocked", 0 },
    { "thirdParties.LongTail Ad Solutions.blocked", 0 },
    { "thirdParties.Sailthru.blocked", 0 },
    { "thirdParties.Marketplace Web Service.blocked", 0 },
    { "thirdParties.Pinterest.blocked", 0 },
    { "thirdParties.BrightTag / Signal.blocked", 0 },
    { "thirdParties.mPulse.blocked", 0 },
    { "thirdParties.ForeSee.blocked", 0 },
    { "thirdParties.Permutive.blocked", 0 },
    { "thirdParties.FirstImpression.blocked", 0 },
    { "thirdParties.Connatix.blocked", 0 },
    { "thirdParties.Media Management Technologies.blocked", 0 },
    { "thirdParties.Mobify.blocked", 0 },
    { "thirdParties.Yieldify.blocked", 0 },
    { "thirdParties.Crazy Egg.blocked", 0 },
    { "thirdParties.SurveyMonkey.blocked", 0 },
    { "thirdParties.Touch Commerce.blocked", 0 },
    { "thirdParties.RichRelevance.blocked", 0 },
    { "thirdParties.Reevoo.blocked", 0 },
    { "thirdParties.Micropat.blocked", 1 },
    { "thirdParties.Playbuzz.blocked", 1 },
    { "thirdParties.Po.st.blocked", 1 },
    { "thirdParties.Fastly.blocked", 0 },
    { "thirdParties.eBay.blocked", 0 },
    { "thirdParties.TRUSTe.blocked", 0 },
    { "thirdParties.Qualtrics.blocked", 0 },
    { "thirdParties.Aggregate Knowledge.blocked", 0 },
    { "thirdParties.Digioh.blocked", 0 },
    { "thirdParties.Gigya.blocked", 0 },
    { "thirdParties.Crowd Control.blocked", 0 },
    { "thirdParties.LinkedIn Ads.blocked", 0 },
    { "thirdParties.Riskified.blocked", 0 },
    { "thirdParties.BlueKai.blocked", 0 },
    { "thirdParties.AMP.blocked", 0 },
    { "thirdParties.eXelate.blocked", 0 },
    { "thirdParties.Captify Media.blocked", 0 },
    { "thirdParties.Hola Networks.blocked", 0 },
    { "thirdParties.Polar Mobile Group.blocked", 0 },
    { "thirdParties.Apester.blocked", 0 },
    { "thirdParties.StreamRail.blocked", 0 },
    { "thirdParties.SpringServer.blocked", 0 },
    { "thirdParties.Monetate.blocked", 0 },
    { "thirdParties.Adobe Scene7.blocked", 0 },
    { "thirdParties.Opta.blocked", 0 },
    { "thirdParties.FLXone.blocked", 0 },
    { "thirdParties.Sift Science.blocked", 0 },
    { "thirdParties.Accuweather.blocked", 0 },
    { "thirdParties.Lucky Orange.blocked", 0 },
    { "thirdParties.AWeber.blocked", 0 },
    { "thirdParties.Salesforce.com.blocked", 0 },
    { "thirdParties.Wistia.blocked", 0 },
    { "thirdParties.Histats.blocked", 0 },
    { "thirdParties.ShareThis.blocked", 0 },
    { "thirdParties.Adyoulike.blocked", 0 },
    { "thirdParties.Pusher.blocked", 0 },
    { "thirdParties.PERFORM.blocked", 0 },
    { "thirdParties.Pingdom RUM.blocked", 0 },
    { "thirdParties.Cloudflare.blocked", 0 },
    { "thirdParties.Hubspot.blocked", 0 },
    { "thirdParties.Curalate.blocked", 0 },
    { "thirdParties.Decibel Insight.blocked", 0 },
    { "thirdParties.Mouseflow.blocked", 0 },
    { "thirdParties.Symantec.blocked", 0 },
    { "thirdParties.Proper Media.blocked", 0 },
    { "thirdParties.Vimeo.blocked", 0 },
    { "thirdParties.LivePerson.blocked", 0 },
    { "thirdParties.Clicktale.blocked", 0 },
    { "thirdParties.iPerceptions.blocked", 0 },
    { "thirdParties.Sekindo.blocked", 0 },
    { "thirdParties.OpenX.blocked", 0 },
    { "thirdParties.Teads.blocked", 0 },
    { "thirdParties.sovrn.blocked", 0 },
    { "thirdParties.GumGum.blocked", 0 },
    { "thirdParties.Microsoft Hosted Libs.blocked", 0 },
    { "thirdParties.Vox Media.blocked", 0 },
    { "thirdParties.Concert.blocked", 0 },
    { "thirdParties.Xaxis.blocked", 0 },
    { "thirdParties.unpkg.blocked", 0 },
    { "thirdParties.Maxymiser.blocked", 0 },
    { "thirdParties.Kaltura Video Platform.blocked", 0 },
    { "thirdParties.SoundCloud.blocked", 0 },
    { "thirdParties.Kargo.blocked", 0 },
    { "thirdParties.TripleLift.blocked", 0 },
    { "thirdParties.Trip Advisor.blocked", 0 },
    { "thirdParties.Cloudinary.blocked", 0 },
    { "thirdParties.Tawk.to.blocked", 0 },
    { "thirdParties.Klevu Search.blocked", 0 },
    { "thirdParties.Yandex APIs.blocked", 0 },
    { "adblockRequests", 20 },
    { "metrics.firstMeaningfulPaint", 129 },
    { "metrics.interactive", 225 },
    { "metrics.observedDomContentLoaded", 225 },
    { "metrics.observedFirstVisualChange", 142 },
    { "metrics.observedLoad", 925 },
    { "resources.document.requestCount", 5 },
    { "resources.document.size", 34662 },
    { "resources.font.requestCount", 3 },
    { "resources.font.size", 317818 },
    { "resources.image.requestCount", 9 },
    { "resources.image.size", 1702888 },
    { "resources.media.requestCount", 0 },
    { "resources.media.size", 0 },
    { "resources.other.requestCount", 1 },
    { "resources.other.size", 324 },
    { "resources.script.requestCount", 32 },
    { "resources.script.size", 238315 },
    { "resources.stylesheet.requestCount", 9 },
    { "resources.third-party.requestCount", 54 },
    { "resources.third-party.size", 2367498 },
    { "resources.stylesheet.size", 90131 },
    { "resources.total.requestCount", 59 },
    { "resources.total.size", 238413 },
  };
  double result = predict(featuremap);
  EXPECT_EQ((int)result, 794393);
}


} // namespace brave_perf_predictor
