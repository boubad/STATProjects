#include "unite.h"
#include "domainconstants.h"
#include "matiere.h"
#include "idatamanager.h"
///////////////////////////////////////
namespace info {
	//////////////////////////
	Unite::Unite()
	{
		this->type(DomainConstants::UNITE_TYPE);
		this->modified(false);
	}
	Unite::Unite(const Value &oMap) :DepSigleNamedItem(oMap) {
		this->type(DomainConstants::UNITE_TYPE);
		this->modified(false);
	}
	Unite::Unite(const Departement &oDep) : DepSigleNamedItem(oDep) {
		this->type(DomainConstants::UNITE_TYPE);
		this->modified(false);
	}
	Unite::Unite(const Unite &other) : DepSigleNamedItem(other) {

	}
	Unite & Unite::operator=(const Unite &other) {
		if (this != &other) {
			DepSigleNamedItem::operator=(other);
		}
		return (*this);
	}

	Unite::~Unite()
	{
	}
	int Unite::order(void) const {
		return this->get_int(DomainConstants::ORDER);
	}
	void Unite::order(int n) {
		this->set_int(DomainConstants::ORDER, n);
	}
	std::string Unite::store_prefix(void) const {
		return (DomainConstants::UNITE_PREFIX);
	}
	std::vector<std::shared_ptr<Matiere>> Unite::matieres(IDataManager &oMan) {
		std::vector<std::shared_ptr<Matiere>> oRet;
		if (this->has_id()) {
			Matiere model(*this);
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
							std::shared_ptr<Matiere> d = std::make_shared<Matiere>(*pv);
							oRet.push_back(d);
						}
					}// i
				}// pAr
			}// array
		}// has_id
		return oRet;
	}
	/////////////////////////////////
}// namespace geninfo
