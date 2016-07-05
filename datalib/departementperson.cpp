#include "departementperson.h"
#include "departement.h"
#include "domainconstants.h"
#include "idatamanager.h"
//////////////////////////////////////
namespace info {
	/////////////////////////////////
	DepartementPerson::DepartementPerson() {

	}
	DepartementPerson::DepartementPerson(const Departement &oDep, const Person &oPers) {
		this->person(oPers);
		this->departement(oDep);
	}
	DepartementPerson::DepartementPerson(const Value &oMap) :PersonItem(oMap) {

	}
	DepartementPerson::DepartementPerson(const DepartementPerson &other) : PersonItem(other) {

	}
	DepartementPerson & DepartementPerson::operator=(const DepartementPerson &other) {
		if (this != &other) {
			PersonItem::operator=(other);
		}
		return (*this);
	}
	DepartementPerson::~DepartementPerson() {

	}
	void DepartementPerson::departement(const Departement &oDep) {
		this->set_string(DomainConstants::DEPARTEMENTID, oDep.id());
	}
	std::string DepartementPerson::departementid(void) const {
		return this->get_string(DomainConstants::DEPARTEMENTID);
	}
	std::shared_ptr<Departement> DepartementPerson::get_departement(IDataManager &oMan) {
		std::shared_ptr<Departement> oRet;
		std::string id = this->personid();
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
	std::string DepartementPerson::start_key(void) const {
		return (this->store_prefix() + this->departementid());
	}
	std::string DepartementPerson::create_id(void) const {
		return this->start_key()  + this->personid();
	}
	bool DepartementPerson::is_storeable(void) const {
		std::string s2 = this->departementid();
		return (!s2.empty()) && PersonItem::is_storeable();
	}
	std::string DepartementPerson::text(void) const {
		return this->fullname();
	}
}// namespace geninfo
