#include <cstdint>
#include <string>
#include <unordered_map>

#include "third_party_extractor.h"
#include "content/public/common/resource_load_info.mojom.h"
#include "components/page_load_metrics/common/page_load_metrics.mojom.h"

namespace brave_savings {

class BandwidthSavingsPredictor {
  public:
    BandwidthSavingsPredictor();
    ~BandwidthSavingsPredictor();

    void OnPageLoadTimingUpdated(const page_load_metrics::mojom::PageLoadTiming& timing);
    void OnSubresourceBlocked(const std::string& resource_url);
    void OnResourceLoadComplete(const content::mojom::ResourceLoadInfo& resource_load_info);
    double predict();

  private:
    ThirdPartyExtractor* third_party_extractor_ = nullptr;
    std::unordered_map<std::string, double> feature_map_;
};

}
