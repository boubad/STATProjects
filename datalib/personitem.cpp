#include "personitem.h"
#include "person.h"
#include "domainconstants.h"
#include "idatamanager.h"
//////////////////////////////////////
namespace info {
	/////////////////////////////////
	PersonItem::PersonItem() {

	}
	PersonItem::PersonItem(const Person &oPers) {
		this->person(oPers);
	}
	PersonItem::PersonItem(const Value &oMap) :BaseItem(oMap) {

	}
	PersonItem::PersonItem(const PersonItem &other) : BaseItem(other) {

	}
	PersonItem & PersonItem::operator=(const PersonItem &other) {
		if (this != &other) {
			BaseItem::operator=(other);
		}
		return (*this);
	}
	PersonItem::~PersonItem() {

	}
	void PersonItem::person(const Person &oPers) {
		this->set_string(DomainConstants::PERSONID, oPers.id());
		this->set_string(DomainConstants::FIRSTNAME, oPers.firstname());
		this->set_string(DomainConstants::LASTNAME, oPers.lastname());
	}
	std::string PersonItem::personid(void) const {
		return this->get_string(DomainConstants::PERSONID);
	}
	void PersonItem::personid(const std::string &s)  {
		this->set_string(DomainConstants::PERSONID,s);
	}
	std::string PersonItem::firstname(void) const {
		return this->get_string(DomainConstants::FIRSTNAME);
	}
	std::string PersonItem::lastname(void) const {
		return this->get_string(DomainConstants::LASTNAME);
	}
	std::string PersonItem::fullname(void) const {
		std::string s = this->lastname() + std::string(" ") + this->firstname();
		return trim(s);
	}
	std::shared_ptr<Person> PersonItem::get_person(IDataManager &oMan) {
		std::shared_ptr<Person> oRet;
		std::string id = this->personid();
		if (id.empty()) {
			Value v = oMan.read_doc(id);
			if (v.is_object()) {
				Object *pObj = v.as_object();
				if (pObj != nullptr) {
					std::string sx = pObj->get_string(DomainConstants::ID);
					if (sx == id) {
						oRet = std::make_shared<Person>(v);
					}
				}// pObj
			}
		}
		return oRet;
	}
	
	bool PersonItem::is_storeable(void) const {
		std::string s2 = this->personid();
		return (!s2.empty()) && BaseItem::is_storeable();
	}
	
	bool PersonItem::save(IDataManager &oMan) {
		std::string s2 = this->personid();
		if (s2.empty()) {
			return (false);
		}
		std::shared_ptr<Person> o = this->get_person(oMan);
		Person *pPers = o.get();
		if (pPers == nullptr) {
			return false;
		}
		if (!pPers->is_storeable()) {
			return false;
		}
		bool b = this->check_person(*pPers);
		if (b) {
			if (!pPers->save(oMan)) {
				return (false);
			}
		}
		return BaseItem::save(oMan);
	}//save
	bool PersonItem::check_person(Person &oPers) {
		bool bRet = false;
		std::string s = this->personid();
		if (s != oPers.id()) {
			this->set_string(DomainConstants::PERSONID, oPers.id());
		}
		s = this->firstname();
		if (s != oPers.firstname()) {
			this->set_string(DomainConstants::FIRSTNAME, oPers.firstname());
		}
		s = this->lastname();
		if (s != oPers.lastname()) {
			this->set_string(DomainConstants::LASTNAME, oPers.lastname());
		}
		return bRet;
	}
}// namespace geninfo
