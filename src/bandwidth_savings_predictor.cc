#include "bandwidth_savings_predictor.h"
#include "predictor.h"

#include "base/logging.h"
#include "content/public/common/resource_type.h"

namespace brave_savings {

BandwidthSavingsPredictor::BandwidthSavingsPredictor(ThirdPartyExtractor* third_party_extractor):
  third_party_extractor_(third_party_extractor) {}

BandwidthSavingsPredictor::~BandwidthSavingsPredictor() = default;

void BandwidthSavingsPredictor::OnPageLoadTimingUpdated(const page_load_metrics::mojom::PageLoadTiming& timing) {
  // First meaningful paint
  if (timing.paint_timing->first_meaningful_paint.has_value()) {
    feature_map_["metrics.firstMeaningfulPaint"] = timing.paint_timing->first_meaningful_paint.value().InMillisecondsF();
  }
  // DOM Content Loaded
  if (timing.document_timing->dom_content_loaded_event_start.has_value()) {
    feature_map_["metrics.observedDomContentLoaded"] = timing.document_timing->dom_content_loaded_event_start.value().InMillisecondsF();
  }
  // First contentful paint
  if (timing.paint_timing->first_contentful_paint.has_value()) {
    feature_map_["metrics.observedFirstVisualChange"] = timing.paint_timing->first_contentful_paint.value().InMillisecondsF();
  }
  // Load
  if (timing.document_timing->load_event_start.has_value()) {
    feature_map_["metrics.observedLoad"] = timing.document_timing->load_event_start.value().InMillisecondsF();
  }
  // Interactive
  if (timing.interactive_timing->interactive.has_value()) {
    feature_map_["metrics.interactive"] = timing.interactive_timing->interactive.value().InMillisecondsF();
  }
}

void BandwidthSavingsPredictor::OnSubresourceBlocked(const std::string& resource_url) {
  feature_map_["adblockRequests"] += 1;
  if (third_party_extractor_) {
    auto entity_name = third_party_extractor_->get_entity(resource_url);
    if (entity_name.has_value()) {
      feature_map_["thirdParties." + entity_name.value() + ".blocked"] = 1;
    }
  }
}

void BandwidthSavingsPredictor::OnResourceLoadComplete(const content::mojom::ResourceLoadInfo& resource_load_info) {
  feature_map_["resources.total.requestCount"] += 1;
  feature_map_["resources.total.size"] += resource_load_info.raw_body_bytes;
  std::string resource_type;
  switch(resource_load_info.resource_type) {
    case content::ResourceType::kMainFrame:
      resource_type = "document";
      break;
    case content::ResourceType::kSubFrame:
      resource_type = "document";
      break;
    case content::ResourceType::kStylesheet:
      resource_type = "stylesheet";
      break;
    case content::ResourceType::kScript:
      resource_type = "script";
      break;
    case content::ResourceType::kImage:
      resource_type = "image";
      break;
    case content::ResourceType::kFontResource:
      resource_type = "font";
      break;
    case content::ResourceType::kMedia:
      resource_type = "media";
      break;
    default:
      resource_type = "other";
      break;
  }
  feature_map_["resources." + resource_type + ".requestCount"] += 1;
  feature_map_["resources." + resource_type + ".size"] += resource_load_info.raw_body_bytes;
}

double BandwidthSavingsPredictor::predict() {
  VLOG(3) << "Predicting on feature map:";
  auto it = feature_map_.begin();
  while(it != feature_map_.end()) {
    VLOG(3) << it->first << " :: " << it->second;
    it++;
  }
  double prediction = ::brave_savings::predict(feature_map_);
  VLOG(2) << "Predicted saving (bytes): " << prediction;
  feature_map_.clear();
  return prediction;
}

}