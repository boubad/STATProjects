#include "depsiglenameitem.h"
#include "domainconstants.h"
#include "departement.h"
#include "idatamanager.h"
//////////////////////////////////
namespace info {

	DepSigleNamedItem::DepSigleNamedItem()
	{
	}
	DepSigleNamedItem::DepSigleNamedItem(const Value &oMap) :SigleNamedItem(oMap) {

	}
	DepSigleNamedItem::DepSigleNamedItem(const Departement &oDep) {
		this->departementid(oDep.id());
	}
	DepSigleNamedItem::DepSigleNamedItem(const DepSigleNamedItem &other) : SigleNamedItem(other) {

	}
	DepSigleNamedItem & DepSigleNamedItem::operator=(const DepSigleNamedItem &other) {
		if (this != &other) {
			SigleNamedItem::operator=(other);
		}
		return (*this);
	}

	DepSigleNamedItem::~DepSigleNamedItem()
	{
	}
	std::string DepSigleNamedItem::departementid(void) const {
		return (this->get_string(DomainConstants::DEPARTEMENTID));
	}
	void DepSigleNamedItem::departementid(const std::string &s) {
		this->set_string(DomainConstants::DEPARTEMENTID, s);
	}
	std::string DepSigleNamedItem::start_key(void) const {
		return (this->store_prefix() + this->departementid());
	}
	bool DepSigleNamedItem::is_storeable(void) const {
		std::string s = this->departementid();
		return ((!s.empty()) && SigleNamedItem::is_storeable());
	}
	std::shared_ptr<Departement> DepSigleNamedItem::get_departement(IDataManager &oMan) const {
		std::shared_ptr<Departement> oRet;
		std::string id = this->departementid();
		if (id.empty()) {
			Value v = oMan.read_doc(id);
			if (v.is_object()) {
				Object *pObj = v.as_object();
				if (pObj != nullptr) {
					std::string sx = pObj->get_string(DomainConstants::ID);
					if (sx == id) {
						oRet = std::make_shared<Departement>(v);
					}
				}// pObj
			}
		}
		return oRet;
	}
	////////////////////////////////////
}// namespace geninfo
