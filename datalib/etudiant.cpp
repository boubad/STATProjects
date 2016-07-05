#include "etudiant.h"
#include "domainconstants.h"
#include "person.h"
#include "idatamanager.h"
/////////////////////////////////////
namespace info {
	////////////////////////
	Etudiant::Etudiant()
	{
		this->type(DomainConstants::ETUDIANT_TYPE);
		this->modified(false);
	}
	Etudiant::Etudiant(const Departement &oDep, const Person &oPers):DepartementPerson(oDep,oPers) {
		this->type(DomainConstants::ETUDIANT_TYPE);
		this->modified(false);
	}
	Etudiant::Etudiant(const Value &oMap):DepartementPerson(oMap) {
		this->type(DomainConstants::ETUDIANT_TYPE);
		this->modified(false);
	}
	Etudiant::Etudiant(const Etudiant &other):DepartementPerson(other) {

	}
	Etudiant & Etudiant::operator=(const Etudiant &other) {
		if (this != &other) {
			DepartementPerson::operator=(other);
		}
		return (*this);
	}

	Etudiant::~Etudiant()
	{
	}
	std::string Etudiant::store_prefix(void) const {
		return (DomainConstants::ETUDIANT_PREFIX);
	}
	bool Etudiant::check_person(Person &oPers) {
		bool bRet = DepartementPerson::check_person(oPers);
		std::string s1 = this->departementid();
		std::string s2 = this->personid();
		if (s1.empty() || s2.empty()) {
			return (bRet);
		}
		std::vector<PersonRole> oRoles = oPers.roles();
		PersonRole r(s1, DomainConstants::ROLE_ETUD);
		bool bFound = false;
		for (auto it = oRoles.begin(); it != oRoles.end(); ++it) {
			if ((*it) == r) {
				bFound = true;
				break;
			}
		}// it
		if (!bFound) {
			std::string depid = this->departementid();
			oPers.add_role(depid,DomainConstants::ROLE_ETUD);
			bRet = true;
		}
		return bRet;
	}
	/////////////////////////////
}// namespace geninfo