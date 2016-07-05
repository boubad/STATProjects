#include "annee.h"
#include "domainconstants.h"
#include "semestre.h"
#include "idatamanager.h"
/////////////////////////////
namespace info {
	//////////////////////
	Annee::Annee()
	{
		this->type(DomainConstants::ANNEE_TYPE);
		this->modified(false);
	}
	Annee::Annee(const Value &oMap) :DepSigleNamedItem(oMap) {
		this->type(DomainConstants::ANNEE_TYPE);
		this->modified(false);
	}
	Annee::Annee(const Departement &dep) : DepSigleNamedItem(dep) {
		this->type(DomainConstants::ANNEE_TYPE);
		this->modified(false);
	}
	Annee::Annee(const Annee &other) : DepSigleNamedItem(other) {

	}
	Annee & Annee::operator=(const Annee &other) {
		if (this != &other) {
			DepSigleNamedItem::operator=(other);
		}
		return *this;
	}

	Annee::~Annee()
	{
	}
	std::string Annee::start_date(void) const {
		return this->get_string(DomainConstants::STARTDATE);
	}
	void Annee::start_date(const std::string &s) {
		this->set_string(DomainConstants::STARTDATE, trim(s));
	}
	std::string Annee::end_date(void) const {
		return this->get_string(DomainConstants::ENDDATE);
	}
	void Annee::end_date(const std::string &s) {
		this->set_string(DomainConstants::ENDDATE, trim(s));
	}
	std::string Annee::store_prefix(void) const {
		return DomainConstants::ANNEE_PREFIX;
	}
	std::string Annee::create_id(void) const {
		return (this->start_key() + this->start_date());
	}
	bool Annee::is_storeable(void) const {
		std::string s1 = this->start_date();
		std::string s2 = this->end_date();
		return (!s1.empty()) && (!s2.empty()) && (s1 >= s1) &&
			DepSigleNamedItem::is_storeable();
	}
	std::vector<std::shared_ptr<Semestre>> Annee::semestres(IDataManager &oMan) {
		std::vector<std::shared_ptr<Semestre>> oRet;
		if (this->has_id()) {
			Semestre model(*this);
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
							std::shared_ptr<Semestre> d = std::make_shared<Semestre>(*pv);
							oRet.push_back(d);
						}
					}// i
				}// pAr
			}// array
		}// has_id
		return oRet;
	}
	//////////////////////
}// namespace geninfo
