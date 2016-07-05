#include "semestre.h"
#include "domainconstants.h"
#include "annee.h"
#include "idatamanager.h"
////////////////////////////////////
namespace info {
	///////////////////////////
	Semestre::Semestre()
	{
		this->type(DomainConstants::SEMESTRE_TYPE);
		this->modified(false);
	}
	Semestre::Semestre(const Value &oMap) :SigleNamedItem(oMap) {
		this->type(DomainConstants::SEMESTRE_TYPE);
		this->modified(false);
	}
	Semestre::Semestre(const Annee &oAnnee) {
		this->anneeid(oAnnee.id());
		this->type(DomainConstants::SEMESTRE_TYPE);
	}
	Semestre::Semestre(const Semestre &other) :SigleNamedItem(other) {

	}
	Semestre & Semestre::operator=(const Semestre &other) {
		if (this != &other) {
			SigleNamedItem::operator=(other);
		}
		return *this;
	}

	Semestre::~Semestre()
	{
	}
	std::string Semestre::anneeid(void) const {
		return this->get_string(DomainConstants::ANNEEID);
	}
	void Semestre::anneeid(const std::string &s) {
		this->set_string(DomainConstants::ANNEEID, s);
	}
	std::string Semestre::start_date(void) const {
		return this->get_string(DomainConstants::STARTDATE);
	}
	void Semestre::start_date(const std::string &s) {
		this->set_string(DomainConstants::STARTDATE, trim(s));
	}
	std::string Semestre::end_date(void) const {
		return this->get_string(DomainConstants::ENDDATE);
	}
	void Semestre::end_date(const std::string &s) {
		this->set_string(DomainConstants::ENDDATE, trim(s));
	}
	std::string Semestre::store_prefix(void) const {
		return DomainConstants::SEMESTRE_PREFIX;
	}
	std::string Semestre::start_key(void) const {
		return (this->store_prefix() + this->anneeid());
	}
	std::string Semestre::create_id(void) const {
		return (this->start_key() + this->start_date());
	}
	bool Semestre::is_storeable(void) const {
		std::string s1 = this->start_date();
		std::string s2 = this->end_date();
		std::string s3 = this->anneeid();
		return (!s1.empty()) && (!s2.empty()) && (s1 >= s1) && (!s3.empty()) &&
			SigleNamedItem::is_storeable();
	}
	std::shared_ptr<Annee> Semestre::get_annee(IDataManager &oMan) const {
		std::shared_ptr<Annee> oRet;
		std::string id = this->anneeid();
		if (id.empty()) {
			Value v = oMan.read_doc(id);
			if (v.is_object()) {
				Object *pObj = v.as_object();
				if (pObj != nullptr) {
					std::string sx = pObj->get_string(DomainConstants::ID);
					if (sx == id) {
						oRet = std::make_shared<Annee>(v);
					}
				}// pObj
			}
		}
		return oRet;
	}
	//////////////////////////
}// namespace geninfo
