#include "affectation.h"
#include "domainconstants.h"
#include "idatamanager.h"
#include "departementperson.h"
#include "semestre.h"
#include "groupe.h"
#include "person.h"
//////////////////////////////////
namespace info {
	//////////////////////////////////
	Affectation::Affectation()
	{
	}

	Affectation::Affectation(const DepartementPerson &oPers,
		const Semestre &oSem, const Groupe &oGroupe) {
		this->personid(oPers.personid());
		this->semestre(oSem);
		this->groupe(oGroupe);
	}
	Affectation::Affectation(const Value &oMap) :PersonItem(oMap) {

	}
	Affectation::Affectation(const Affectation &other) : PersonItem(other) {

	}
	Affectation & Affectation::operator=(const Affectation &other) {
		if (this != &other) {
			PersonItem::operator=(other);
		}
		return *this;
	}
	Affectation::~Affectation()
	{
	}
	std::string Affectation::anneeid(void) const {
		return this->get_string(DomainConstants::ANNEEID);
	}
	void Affectation::anneeid(const std::string &s) {
		this->set_string(DomainConstants::ANNEEID, s);
	}
	std::string Affectation::semestreid(void) const {
		return this->get_string(DomainConstants::SEMESTREID);
	}
	void Affectation::semestreid(const std::string &s) {
		this->set_string(DomainConstants::SEMESTREID, s);
	}
	std::string Affectation::groupeid(void) const {
		return this->get_string(DomainConstants::GROUPEID);
	}
	void Affectation::groupeid(const std::string &s) {
		this->set_string(DomainConstants::GROUPEID, s);
	}
	void Affectation::semestre(const Semestre &oSem) {
		this->semestreid(oSem.id());
		this->anneeid(oSem.anneeid());
	}
	void Affectation::groupe(const Groupe &oGroupe) {
		this->groupeid(oGroupe.id());
	}
	std::string Affectation::start_date(void) const {
		return this->get_string(DomainConstants::STARTDATE);
	}
	void Affectation::start_date(const std::string &s) {
		this->set_string(DomainConstants::STARTDATE, s);
	}
	std::string Affectation::end_date(void) const {
		return this->get_string(DomainConstants::ENDDATE);
	}
	void Affectation::end_date(const std::string &s) {
		this->set_string(DomainConstants::ENDDATE, s);
	}
	std::shared_ptr<Groupe> Affectation::get_groupe(IDataManager &oMan) {
		std::shared_ptr<Groupe> oRet;
		std::string id = this->groupeid();
		if (id.empty()) {
			Value v = oMan.read_doc(id);
			if (v.is_object()) {
				Object *pObj = v.as_object();
				if (pObj != nullptr) {
					std::string sx = pObj->get_string(DomainConstants::ID);
					if (sx == id) {
						oRet = std::make_shared<Groupe>(v);
					}
				}// pObj
			}
		}
		return oRet;
	}
	std::shared_ptr<Semestre> Affectation::get_semestre(IDataManager &oMan) {
		std::shared_ptr<Semestre> oRet;
		std::string id = this->personid();
		if (id.empty()) {
			Value v = oMan.read_doc(id);
			if (v.is_object()) {
				Object *pObj = v.as_object();
				if (pObj != nullptr) {
					std::string sx = pObj->get_string(DomainConstants::ID);
					if (sx == id) {
						oRet = std::make_shared<Semestre>(v);
					}
				}// pObj
			}
		}
		return oRet;
	}
	bool Affectation::is_storeable(void) const {
		std::string s1 = this->groupeid();
		std::string s2 = this->semestreid();
		return (!s1.empty()) && (!s2.empty()) && PersonItem::is_storeable();
	}
	std::string Affectation::start_key(void) const {
		return this->store_prefix() + this->semestreid();
	}
	bool Affectation::check_person(Person &oPers) {
		bool bRet = PersonItem::check_person(oPers);
		std::string s = this->semestreid();
		if (!s.empty()) {
			std::set <std::string> oSet = oPers.semestreids();
			if (oSet.find(s) != oSet.end()) {
				oPers.add_semestreid(s);
				bRet = true;
			}
		}
		s = this->groupeid();
		if (!s.empty()) {
			std::set <std::string> oSet = oPers.groupeids();
			if (oSet.find(s) != oSet.end()) {
				oPers.add_groupeid(s);
				bRet = true;
			}
		}
		s = this->anneeid();
		if (!s.empty()) {
			std::set <std::string> oSet = oPers.anneeids();
			if (oSet.find(s) != oSet.end()) {
				oPers.add_anneeid(s);
				bRet = true;
			}
		}
		return bRet;
	}// check_person
	//////////////////////////////////
}// namespace geninfo
