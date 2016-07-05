#include "enseignantaffectation.h"
#include "domainconstants.h"
#include "enseignant.h"
#include "matiere.h"
#include "idatamanager.h"
//////////////////////////////////
namespace info {
	////////////////////////////////////
	std::vector<std::shared_ptr<EnseignantAffectation> >
		EnseignantAffectation::get_all_affectations(IDataManager &oMan,
			const std::string &semid /*= std::string()*/,
			const std::string &matid  /*= std::string()*/,
			const std::string &groupeid /*= std::string()*/,
			int skip /*= 0*/, int limit /*= 0*/) {
		std::vector<std::shared_ptr<EnseignantAffectation> > oRet;
		std::string start = DomainConstants::ENSEIGNANTAFFECTATION_PREFIX +
			semid + matid + groupeid;
		std::string end = start + std::string("zzzzzz");
		Value vr = oMan.read_docs_range(start, end, skip, limit);
		if (vr.is_array()) {
			Array *pAr = vr.as_array();
			if (pAr != nullptr) {
				size_t n = pAr->size();
				for (size_t i = 0; i < n; ++i) {
					PValue ov = (*pAr)[i];
					Value *pv = ov.get();
					if (pv != nullptr) {
						std::shared_ptr<EnseignantAffectation> d = std::make_shared<EnseignantAffectation>(*pv);
						oRet.push_back(d);
					}
				}// i
			}// pAr
		}// array
		return oRet;
	}//get_all_affectations
	//////////////////////////////////////
	EnseignantAffectation::EnseignantAffectation()
	{
		this->type(DomainConstants::ENSEIGNANTAFFECTATION_TYPE);
		this->modified(false);
	}

	EnseignantAffectation::EnseignantAffectation(const Enseignant &oProf,
		const Semestre &oSem, const Matiere &oMat, const Groupe &oGroupe) :Affectation(oProf, oSem, oGroupe) {
		this->type(DomainConstants::ENSEIGNANTAFFECTATION_TYPE);
		this->enseignant(oProf);
		this->matiere(oMat);
		this->modified(false);
	}
	EnseignantAffectation::EnseignantAffectation(const Value &oMap) : Affectation(oMap) {
		this->type(DomainConstants::ENSEIGNANTAFFECTATION_TYPE);
		this->modified(false);
	}
	EnseignantAffectation::EnseignantAffectation(const EnseignantAffectation &other) : Affectation(other) {

	}
	EnseignantAffectation & EnseignantAffectation::operator=(const EnseignantAffectation &other) {
		if (this != &other) {
			Affectation::operator=(other);
		}
		return *this;
	}
	EnseignantAffectation::~EnseignantAffectation()
	{
	}
	std::string EnseignantAffectation::enseignantid(void) const {
		return this->get_string(DomainConstants::ENSEIGNANTID);
	}
	void EnseignantAffectation::enseignantid(const std::string &s) {
		this->set_string(DomainConstants::ENSEIGNANTID, s);
	}
	void EnseignantAffectation::enseignant(const Enseignant &oProf) {
		this->enseignantid(oProf.id());
		this->personid(oProf.personid());
	}
	std::string EnseignantAffectation::matiereid(void) const {
		return this->get_string(DomainConstants::MATIEREID);
	}
	void EnseignantAffectation::matiereid(const std::string &s) {
		this->set_string(DomainConstants::MATIEREID, s);
	}
	void EnseignantAffectation::matiere(const Matiere &oMat) {
		this->matiereid(oMat.id());
	}
	std::shared_ptr<Enseignant> EnseignantAffectation::get_enseignant(IDataManager &oMan) {
		std::shared_ptr<Enseignant> oRet;
		std::string id = this->enseignantid();
		if (id.empty()) {
			Value v = oMan.read_doc(id);
			if (v.is_object()) {
				Object *pObj = v.as_object();
				if (pObj != nullptr) {
					std::string sx = pObj->get_string(DomainConstants::ID);
					if (sx == id) {
						oRet = std::make_shared<Enseignant>(v);
					}
				}// pObj
			}
		}
		return oRet;
	}
	std::shared_ptr<Matiere> EnseignantAffectation::get_matiere(IDataManager &oMan) {
		std::shared_ptr<Matiere> oRet;
		std::string id = this->matiereid();
		if (id.empty()) {
			Value v = oMan.read_doc(id);
			if (v.is_object()) {
				Object *pObj = v.as_object();
				if (pObj != nullptr) {
					std::string sx = pObj->get_string(DomainConstants::ID);
					if (sx == id) {
						oRet = std::make_shared<Matiere>(v);
					}
				}// pObj
			}
		}
		return oRet;
	}
	std::string EnseignantAffectation::store_prefix(void) const {
		return DomainConstants::ENSEIGNANTAFFECTATION_PREFIX;
	}
	std::string EnseignantAffectation::start_key(void) const {
		return this->store_prefix() + this->semestreid() + this->matiereid() +
			this->groupeid();
	}
	std::string EnseignantAffectation::create_id(void) const {
		return this->start_key() + this->enseignantid();
	}
	bool EnseignantAffectation::is_storeable(void) const {
		std::string s = this->enseignantid();
		std::string s2 = this->matiereid();
		return (!s.empty()) && (!s2.empty()) && Affectation::is_storeable();
	}
	///////////////////////////////////////
}// namespace geninfo
