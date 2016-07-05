#include "enseignant.h"
#include "domainconstants.h"
#include "person.h"
#include "idatamanager.h"
/////////////////////////////////////
namespace info {
	////////////////////////
	Enseignant::Enseignant()
	{
		this->type(DomainConstants::ENSEIGNANT_TYPE);
		this->modified(false);
	}
	Enseignant::Enseignant(const Departement &oDep, const Person &oPers) :DepartementPerson(oDep, oPers) {
		this->type(DomainConstants::ENSEIGNANT_TYPE);
		this->modified(false);
	}
	Enseignant::Enseignant(const Value &oMap) : DepartementPerson(oMap) {
		this->type(DomainConstants::ENSEIGNANT_TYPE);
		this->modified(false);
	}
	Enseignant::Enseignant(const Enseignant &other) : DepartementPerson(other) {

	}
	Enseignant & Enseignant::operator=(const Enseignant &other) {
		if (this != &other) {
			DepartementPerson::operator=(other);
		}
		return (*this);
	}

	Enseignant::~Enseignant()
	{
	}
	std::string Enseignant::store_prefix(void) const {
		return (DomainConstants::ENSEIGNANT_PREFIX);
	}
	bool Enseignant::check_person(Person &oPers) {
		bool bRet = DepartementPerson::check_person(oPers);
		std::string s1 = this->departementid();
		std::string s2 = this->personid();
		if (s1.empty() || s2.empty()) {
			return (bRet);
		}
		std::vector<PersonRole> oRoles = oPers.roles();
		PersonRole r(s1, DomainConstants::ROLE_PROF);
		bool bFound = false;
		for (auto it = oRoles.begin(); it != oRoles.end(); ++it) {
			if ((*it) == r) {
				bFound = true;
				break;
			}
		}// it
		if (!bFound) {
			std::string depid = this->departementid();
			oPers.add_role(depid, DomainConstants::ROLE_PROF);
			bRet = true;
		}
		return bRet;
	}
	/////////////////////////////
}// namespace geninfo