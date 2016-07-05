#include "departement.h"
#include "domainconstants.h"
#include "idatamanager.h"
#include "unite.h"
#include "groupe.h"
#include "annee.h"
#include "enseignant.h"
#include "etudiant.h"
#include "administrator.h"
#include "person.h"
//////////////////////////////
namespace info {
	//////////////////////////////////////
	std::vector<PDepartement> Departement::get_all_departements(IDataManager &oMan, int skip /*= 0*/, int count /*= 10*/) {
		std::vector<PDepartement> oRet;
		Departement model;
		Value vr = oMan.read_docs_range(model.start_key(), model.end_key(),skip,count);
		if (vr.is_array()) {
			Array *pAr = vr.as_array();
			if (pAr != nullptr) {
				size_t n = pAr->size();
				for (size_t i = 0; i < n; ++i) {
					PValue ov = (*pAr)[i];
					Value *pv = ov.get();
					if (pv != nullptr) {
						PDepartement d = std::make_shared<Departement>(*pv);
						oRet.push_back(d);
					}
				}// i
			}// pAr
		}// array
		return oRet;
	}
	Departement::Departement()
	{
		this->type(DomainConstants::DEPARTEMENT_TYPE);
		this->modified(false);
	}
	Departement::Departement(const Value &oMap):SigleNamedItem(oMap) {
		this->type(DomainConstants::DEPARTEMENT_TYPE);
		this->modified(false);
	}
	Departement::Departement(const Departement &other):SigleNamedItem(other) {

	}
	Departement & Departement::operator=(const Departement & other) {
		if (this != &other) {
			SigleNamedItem::operator=(other);
		}
		return *this;
	}

	Departement::~Departement()
	{
	}
	std::string Departement::store_prefix(void) const {
		return DomainConstants::DEPARTEMENT_PREFIX;
	}
	std::vector<std::shared_ptr<Groupe>> Departement::groupes(IDataManager &oMan) {
		std::vector<std::shared_ptr<Groupe>> oRet;
		if (this->has_id()) {
			Groupe model(*this);
			std::string start = model.start_key();
			std::string end = model.end_key();
			Value vr = oMan.read_docs_range(start, end);
			if (vr.is_array()) {
				Array *pAr = vr.as_array();
				if (pAr != nullptr) {
					size_t n = pAr->size();
					for (size_t i = 0; i < n; ++i) {
						PValue ov = (*pAr)[i];
						Value *pv = ov.get();
						if (pv != nullptr) {
							std::shared_ptr<Groupe> d = std::make_shared<Groupe>(*pv);
							oRet.push_back(d);
						}
					}// i
				}// pAr
			}// array
		}// has_id
		return oRet;
	}
	std::vector<std::shared_ptr<Unite>> Departement::unites(IDataManager &oMan) {
		std::vector<std::shared_ptr<Unite>> oRet;
		if (this->has_id()) {
			Unite model(*this);
			std::string start = model.start_key();
			std::string end = model.end_key();
			Value vr = oMan.read_docs_range(start, end);
			if (vr.is_array()) {
				Array *pAr = vr.as_array();
				if (pAr != nullptr) {
					size_t n = pAr->size();
					for (size_t i = 0; i < n; ++i) {
						PValue ov = (*pAr)[i];
						Value *pv = ov.get();
						if (pv != nullptr) {
							std::shared_ptr<Unite> d = std::make_shared<Unite>(*pv);
							oRet.push_back(d);
						}
					}// i
				}// pAr
			}// array
		}// has_id
		return oRet;
	}
	std::vector<std::shared_ptr<Annee>> Departement::annees(IDataManager &oMan) {
		std::vector<std::shared_ptr<Annee>> oRet;
		if (this->has_id()) {
			Annee model(*this);
			std::string start = model.start_key();
			std::string end = model.end_key();
			Value vr = oMan.read_docs_range(start, end);
			if (vr.is_array()) {
				Array *pAr = vr.as_array();
				if (pAr != nullptr) {
					size_t n = pAr->size();
					for (size_t i = 0; i < n; ++i) {
						PValue ov = (*pAr)[i];
						Value *pv = ov.get();
						if (pv != nullptr) {
							std::shared_ptr<Annee> d = std::make_shared<Annee>(*pv);
							oRet.push_back(d);
						}
					}// i
				}// pAr
			}// array
		}// has_id
		return oRet;
	}
	std::vector<std::shared_ptr<Enseignant>> Departement::enseignants(IDataManager &oMan, int skip /*= 0*/, int count /*= 10*/) {
		std::vector<std::shared_ptr<Enseignant>> oRet;
		if (this->has_id()) {
			Person oPers;
			 Enseignant model(*this,oPers);
			std::string start = model.start_key();
			std::string end = model.end_key();
			Value vr = oMan.read_docs_range(start, end,skip,count);
			if (vr.is_array()) {
				Array *pAr = vr.as_array();
				if (pAr != nullptr) {
					size_t n = pAr->size();
					for (size_t i = 0; i < n; ++i) {
						PValue ov = (*pAr)[i];
						Value *pv = ov.get();
						if (pv != nullptr) {
							std::shared_ptr<Enseignant> d = std::make_shared<Enseignant>(*pv);
							oRet.push_back(d);
						}
					}// i
				}// pAr
			}// array
		}// has_id
		return oRet;
	}
	std::vector<std::shared_ptr<Etudiant>>  Departement::etudiants(IDataManager &oMan, int skip /*= 0*/, int count /*= 10*/) {
		std::vector<std::shared_ptr<Etudiant>> oRet;
		if (this->has_id()) {
			Person oPers;
			Etudiant model(*this, oPers);
			std::string start = model.start_key();
			std::string end = model.end_key();
			Value vr = oMan.read_docs_range(start, end, skip, count);
			if (vr.is_array()) {
				Array *pAr = vr.as_array();
				if (pAr != nullptr) {
					size_t n = pAr->size();
					for (size_t i = 0; i < n; ++i) {
						PValue ov = (*pAr)[i];
						Value *pv = ov.get();
						if (pv != nullptr) {
							std::shared_ptr<Etudiant> d = std::make_shared<Etudiant>(*pv);
							oRet.push_back(d);
						}
					}// i
				}// pAr
			}// array
		}// has_id
		return oRet;
	}
	std::vector<std::shared_ptr<Administrator>>  Departement::administrators(IDataManager &oMan, int skip /*= 0*/, int count /*= 10*/) {
		std::vector<std::shared_ptr<Administrator>> oRet;
		if (this->has_id()) {
			Person oPers;
			Enseignant model(*this, oPers);
			std::string start = model.start_key();
			std::string end = model.end_key();
			Value vr = oMan.read_docs_range(start, end, skip, count);
			if (vr.is_array()) {
				Array *pAr = vr.as_array();
				if (pAr != nullptr) {
					size_t n = pAr->size();
					for (size_t i = 0; i < n; ++i) {
						PValue ov = (*pAr)[i];
						Value *pv = ov.get();
						if (pv != nullptr) {
							std::shared_ptr<Administrator> d = std::make_shared<Administrator>(*pv);
							oRet.push_back(d);
						}
					}// i
				}// pAr
			}// array
		}// has_id
		return oRet;
	}
	///////////////////////////////////
}// namespace geninfo
