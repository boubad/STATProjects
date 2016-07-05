#include "matiere.h"
#include "domainconstants.h"
#include "unite.h"
#include "idatamanager.h"
/////////////////////////////////
namespace info {
	///////////////////////////////
	Matiere::Matiere()
	{
		this->type(DomainConstants::MATIERE_TYPE);
		this->modified(false);
	}
	Matiere::Matiere(const Value &oMap) :SigleNamedItem(oMap) {
		this->type(DomainConstants::MATIERE_TYPE);
		this->modified(false);
	}
	Matiere::Matiere(const Unite &oUnite) {
		this->uniteid(oUnite.id());
		this->type(DomainConstants::MATIERE_TYPE);
	}
	Matiere::Matiere(const Matiere &other) :SigleNamedItem(other) {

	}
	Matiere & Matiere::operator=(const Matiere &other) {
		if (this != &other) {
			SigleNamedItem::operator=(other);
		}
		return *this;
	}

	Matiere::~Matiere()
	{
	}
	std::string Matiere::uniteid(void) const {
		return this->get_string(DomainConstants::UNITEID);
	}
	void Matiere::uniteid(const std::string &s) {
		this->set_string(DomainConstants::UNITEID, s);
	}
	std::string Matiere::genre(void) const {
		return this->get_string(DomainConstants::GENRE);
	}
	void Matiere::genre(const std::string &s) {
		this->set_string(DomainConstants::GENRE, to_upper(trim(s)));
	}
	std::string Matiere::module(void) const {
		return this->get_string(DomainConstants::MODULE);
	}
	void Matiere::module(const std::string &s) {
		this->set_string(DomainConstants::MODULE, to_upper(trim(s)));
	}
	int Matiere::order(void) const {
		return this->get_int(DomainConstants::ORDER);
	}
	void Matiere::order(int n) {
		this->set_int(DomainConstants::ORDER, n);
	}
	double Matiere::coefficient(void) const {
		double d = this->get_double(DomainConstants::COEFFICIENT);
		return (d > 0.0) ? d : 1.0;
	}
	void Matiere::coefficient(double n) {
		double d = (n > 0.0) ? n : 1.0;
		this->set_double(DomainConstants::COEFFICIENT, d);
	}
	double Matiere::ecs(void) const {
		double d = this->get_double(DomainConstants::ECS);
		return (d >= 0.0) ? d : 0.0;
	}
	void Matiere::ecs(double n) {
		double d = (n >= 0.0) ? n : 0.0;
		this->set_double(DomainConstants::ECS, d);
	}
	std::string Matiere::store_prefix(void) const {
		return DomainConstants::MATIERE_PREFIX;
	}
	std::string Matiere::start_key(void) const {
		return (this->store_prefix() + this->uniteid());
	}
	std::string Matiere::create_id(void) const {
		return (this->start_key() + this->sigle());
	}
	bool Matiere::is_storeable(void) const {
		std::string s1 = this->genre();
		std::string s2 = this->uniteid();
		return (!s1.empty()) && (!s2.empty()) && (s1 >= s1) && 
			SigleNamedItem::is_storeable();
	}
	std::shared_ptr<Unite> Matiere::get_unite(IDataManager &oMan) const {
		std::shared_ptr<Unite> oRet;
		std::string id = this->uniteid();
		if (id.empty()) {
			Value v = oMan.read_doc(id);
			if (v.is_object()) {
				Object *pObj = v.as_object();
				if (pObj != nullptr) {
					std::string sx = pObj->get_string(DomainConstants::ID);
					if (sx == id) {
						oRet = std::make_shared<Unite>(v);
					}
				}// pObj
			}
		}
		return oRet;
	}
	//////////////////////////
}// namespace geninfo
