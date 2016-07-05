#include "siglenameitem.h"
#include "domainconstants.h"
////////////////////////////////
namespace info {
	SigleNamedItem::SigleNamedItem()
	{
	}
	SigleNamedItem::SigleNamedItem(const Value &oMap) :BaseItem(oMap) {

	}
	SigleNamedItem::SigleNamedItem(const SigleNamedItem &other) : BaseItem(other) {

	}
	SigleNamedItem & SigleNamedItem::operator=(const SigleNamedItem &other) {
		if (this != &other) {
			BaseItem::operator=(other);
		}
		return (*this);
	}

	SigleNamedItem::~SigleNamedItem()
	{
	}
	std::string SigleNamedItem::sigle(void) const {
		return (this->get_string(DomainConstants::SIGLE));
	}
	void SigleNamedItem::sigle(const std::string &s) {
		this->set_string(DomainConstants::SIGLE, to_upper(trim(s)));
	}
	std::string SigleNamedItem::name(void) const {
		return (this->get_string(DomainConstants::NAME));
	}
	void SigleNamedItem::name(const std::string &s) {
		this->set_string(DomainConstants::NAME, format_name(s));
	}
	std::string SigleNamedItem::create_id(void) const {
		return (this->start_key() + this->sigle());
	}
	bool SigleNamedItem::is_storeable(void) const {
		std::string s1 = this->sigle();
		std::string s2 = this->name();
		return (!s1.empty()) && (!s2.empty()) && BaseItem::is_storeable();
	}
	std::string SigleNamedItem::text(void) const {
		std::string sRet = this->name();
		if (sRet.empty()) {
			sRet = this->sigle();
		}
		return sRet;
	}
}// namespace geninfo
