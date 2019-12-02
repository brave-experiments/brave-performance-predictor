#include "third_party_extractor.h"

#include "third_party/re2/src/re2/re2.h"

RE2 DOMAIN_IN_URL_REGEX("/:\\/\\/(.*?)(\\/|$)/");
RE2 DOMAIN_CHARACTERS("/[a-z0-9.-]+\\.[a-z0-9]+/i");
RE2 ROOT_DOMAIN_REGEX("/[^.]+\\.([^.]+|(gov|com|co|ne)\\.\\w{2})$/i");

namespace brave_savings {

ThirdPartyExtractor::ThirdPartyExtractor(const std::string& entities) {

}

ThirdPartyExtractor::~ThirdPartyExtractor() = default;

std::string ThirdPartyExtractor::get_entity(const std::string& domain) {
	return "";
}

}