#include "etudiantaffectation.h"
#include "domainconstants.h"
#include "etudiant.h"
#include "idatamanager.h"
//////////////////////////////////
namespace info {
	//////////////////////////////////////////////
	std::vector<std::shared_ptr<EtudiantAffectation> >
		EtudiantAffectation::get_all_affectations(IDataManager &oMan,
			const std::string &semid /*= std::string()*/,
			const std::string &groupeid /*= std::string()*/,
			int skip /*= 0*/, int limit /*= 0*/) {
		std::vector<std::shared_ptr<EtudiantAffectation> > oRet;
		std::string start = DomainConstants::ETUDIANTAFFECTATION_PREFIX +
			semid + groupeid;
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
						std::shared_ptr<EtudiantAffectation> d = std::make_shared<EtudiantAffectation>(*pv);
						oRet.push_back(d);
					}
				}// i
			}// pAr
		}// array
		return oRet;
	}//get_all_affectations
	///////////////////////////////////////////////
	EtudiantAffectation::EtudiantAffectation()
	{
		this->type(DomainConstants::ETUDIANTAFFECTATION_TYPE);
		this->modified(false);
	}

	EtudiantAffectation::EtudiantAffectation(const Etudiant &oEtud,
		const Semestre &oSem, const Groupe &oGroupe) :Affectation(oEtud, oSem, oGroupe) {
		this->type(DomainConstants::ETUDIANTAFFECTATION_TYPE);
		this->etudiant(oEtud);
		this->modified(false);
	}
	EtudiantAffectation::EtudiantAffectation(const Value &oMap) : Affectation(oMap) {
		this->type(DomainConstants::ETUDIANTAFFECTATION_TYPE);
		this->modified(false);
	}
	EtudiantAffectation::EtudiantAffectation(const EtudiantAffectation &other) : Affectation(other) {

	}
	EtudiantAffectation & EtudiantAffectation::operator=(const EtudiantAffectation &other) {
		if (this != &other) {
			Affectation::operator=(other);
		}
		return *this;
	}
	EtudiantAffectation::~EtudiantAffectation()
	{
	}
	std::string EtudiantAffectation::etudiantid(void) const {
		return this->get_string(DomainConstants::ETUDIANTID);
	}
	void EtudiantAffectation::etudiantid(const std::string &s) {
		this->set_string(DomainConstants::ETUDIANTID, s);
	}
	void EtudiantAffectation::etudiant(const Etudiant &oEtud) {
		this->etudiantid(oEtud.id());
		this->personid(oEtud.personid());
	}
	std::shared_ptr<Etudiant> EtudiantAffectation::get_etudiant(IDataManager &oMan) {
		std::shared_ptr<Etudiant> oRet;
		std::string id = this->etudiantid();
		if (id.empty()) {
			Value v = oMan.read_doc(id);
			if (v.is_object()) {
				Object *pObj = v.as_object();
				if (pObj != nullptr) {
					std::string sx = pObj->get_string(DomainConstants::ID);
					if (sx == id) {
						oRet = std::make_shared<Etudiant>(v);
					}
				}// pObj
			}
		}
		return oRet;
	}
	std::string EtudiantAffectation::store_prefix(void) const {
		return DomainConstants::ETUDIANTAFFECTATION_PREFIX;
	}
	std::string EtudiantAffectation::start_key(void) const {
		return this->store_prefix() + this->semestreid() +
			this->groupeid();
	}
	std::string EtudiantAffectation::create_id(void) const {
		return this->start_key() + this->etudiantid();
	}
	bool EtudiantAffectation::is_storeable(void) const {
		std::string s = this->etudiantid();
		return (!s.empty()) && Affectation::is_storeable();
	}
	///////////////////////////////////////
}// namespace geninfo
