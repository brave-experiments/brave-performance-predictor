#include <cstdint>
#include <string>
#include <unordered_map>

#include "base/values.h"

namespace brave_savings {

class ThirdPartyExtractor {
  public:
    ThirdPartyExtractor();
    ~ThirdPartyExtractor();

    bool load_entities(const std::string& entities);
    base::Optional<std::string> get_entity(const std::string& domain);

  private:
    std::unordered_map<std::string, std::string> entity_by_domain_;
    std::unordered_map<std::string, std::string> entity_by_root_domain_;
};

}
