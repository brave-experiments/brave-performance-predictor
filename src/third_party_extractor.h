#include <cstdint>
#include <string>
#include <unordered_map>

namespace brave_savings {

class ThirdPartyExtractor {
  public:
    ThirdPartyExtractor(const std::string& entities);
    ~ThirdPartyExtractor();

    std::string get_entity(const std::string& domain);

  private:
  	std::unordered_map<std::string, std::string> entity_by_domain_;
  	std::unordered_map<std::string, std::string> entity_by_root_domain_;
}

}