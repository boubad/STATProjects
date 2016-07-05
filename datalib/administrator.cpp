#include "administrator.h"
#include "domainconstants.h"
#include "person.h"
#include "idatamanager.h"
/////////////////////////////////////
namespace info {
	////////////////////////
	Administrator::Administrator()
	{
		this->type(DomainConstants::ADMINISTRATOR_TYPE);
		this->modified(false);
	}
	Administrator::Administrator(const Departement &oDep, const Person &oPers) :DepartementPerson(oDep, oPers) {
		this->type(DomainConstants::ADMINISTRATOR_TYPE);
		this->modified(false);
	}
	Administrator::Administrator(const Value &oMap) : DepartementPerson(oMap) {
		this->type(DomainConstants::ADMINISTRATOR_TYPE);
		this->modified(false);
	}
	Administrator::Administrator(const Administrator &other) : DepartementPerson(other) {

	}
	Administrator & Administrator::operator=(const Administrator &other) {
		if (this != &other) {
			DepartementPerson::operator=(other);
		}
		return (*this);
	}

	Administrator::~Administrator()
	{
	}
	std::string Administrator::store_prefix(void) const {
		return (DomainConstants::ADMINISTRATOR_PREFIX);
	}
	bool Administrator::check_person(Person &oPers) {
		bool bRet = DepartementPerson::check_person(oPers);
		std::string s1 = this->departementid();
		std::string s2 = this->personid();
		if (s1.empty() || s2.empty()) {
			return (bRet);
		}
		std::vector<PersonRole> oRoles = oPers.roles();
		PersonRole r(s1, DomainConstants::ROLE_ADMIN);
		bool bFound = false;
		for (auto it = oRoles.begin(); it != oRoles.end(); ++it) {
			if ((*it) == r) {
				bFound = true;
				break;
			}
		}// it
		if (!bFound) {
			std::string depid = this->departementid();
			oPers.add_role(depid, DomainConstants::ROLE_ADMIN);
			bRet = true;
		}
		return bRet;
	}
	/////////////////////////////
}// namespace geninfo