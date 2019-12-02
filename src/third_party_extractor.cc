#include "third_party_extractor.h"

#include "base/logging.h"
#include "base/values.h"
#include "third_party/re2/src/re2/re2.h"
#include "rapidjson/document.h"
#include "rapidjson/error/en.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

RE2 DOMAIN_IN_URL_REGEX(":\\/\\/(.*?)(\\/|$)");
RE2 DOMAIN_CHARACTERS("([a-z0-9.-]+\\.[a-z0-9]+)");
RE2 ROOT_DOMAIN_REGEX("([^.]+\\.([^.]+|(gov|com|co|ne)\\.\\w{2})$)");

namespace brave_savings {

base::Optional<std::string> get_domain_from_origin_or_url(const std::string &origin_or_url) {
    std::string domain;
    // std::string t;
    if (RE2::PartialMatch(origin_or_url, DOMAIN_IN_URL_REGEX, &domain)) {
        return domain;
    }
    if (RE2::PartialMatch(origin_or_url, DOMAIN_CHARACTERS, &domain)) {
        return domain;
    }
    return base::nullopt;
}

std::string get_root_domain(const std::string &domain) {
    std::string root_domain;
    if (RE2::PartialMatch(domain, ROOT_DOMAIN_REGEX, &root_domain)) {
        return root_domain;
    } else {
        return domain;
    }
}

ThirdPartyExtractor::ThirdPartyExtractor(const std::string& entities) {
  rapidjson::Document document;
  document.Parse(entities.c_str());

  if (document.HasParseError()) {
    LOG(ERROR) << "Third Party Extractor failed to parse mapping JSON";
    return;
  }

  if (!document.IsArray()) {
    LOG(ERROR) << "Third Party JSON invalid";
    return;
  }

  for (rapidjson::SizeType i = 0; i < document.Size(); i++) {
    const std::string entity_name = document[i]["name"].GetString();
    const rapidjson::Value& entity_domains = document[i]["domains"];
    if (!entity_domains.IsArray()) {
      continue;
    }
    for (rapidjson::SizeType d = 0; d < entity_domains.Size(); d++) {
      auto* domain = entity_domains[d].GetString();
      LOG(ERROR) << entity_name << " domain " << domain;
      auto domain_entity = entity_by_domain_.find(domain);
      if (domain_entity != entity_by_domain_.end()) {
        LOG(ERROR) << "Duplicate domain " << domain;
      } else {
        entity_by_domain_.emplace(domain, entity_name);
        auto root_domain = get_root_domain(domain);
        
          auto root_domain_entity = entity_by_root_domain_.find(root_domain);
          if (root_domain_entity != entity_by_root_domain_.end() && root_domain_entity->second != entity_name) {
            entity_by_root_domain_.erase(root_domain_entity);
          } else {
            entity_by_root_domain_.emplace(root_domain, entity_name);
          }
        
      }
    }
  }
}

ThirdPartyExtractor::~ThirdPartyExtractor() = default;

base::Optional<std::string> ThirdPartyExtractor::get_entity(const std::string& origin_or_url) {
    base::Optional<std::string> domain = get_domain_from_origin_or_url(origin_or_url);
    if (domain.has_value()) {
        LOG(ERROR) << "Getting entity for domain " << domain.value();
        auto e_domain = entity_by_domain_.find(domain.value());
        if (e_domain != entity_by_domain_.end()) {
            LOG(ERROR) << "Got entity for domain " << domain.value() << ": " << e_domain->second;
            return e_domain->second;
        }
        
        auto root_domain = get_root_domain(domain.value());
        
        LOG(ERROR) << "Getting entity for root domain " << root_domain;
        auto r_domain = entity_by_root_domain_.find(root_domain);
        if (r_domain != entity_by_root_domain_.end()) {
            LOG(ERROR) << "Got entity for root domain " << root_domain << ": " << r_domain->second;
            return r_domain->second;
        }
        
        LOG(ERROR) << "No Entity for " << domain.value();
    } else {
        LOG(ERROR) << "No valid domain in " << origin_or_url;
    }

    return base::nullopt;
}

}