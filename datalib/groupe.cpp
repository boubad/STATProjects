#include "groupe.h"
#include "domainconstants.h"
#include "idatamanager.h"
///////////////////////////////////
namespace info {
	/////////////////////////////
	const std::string Groupe::GENRE_PROMO(DomainConstants::GENRE_PROMO);
	const std::string Groupe::GENRE_TD(DomainConstants::GENRE_TD);
	const std::string Groupe::GENRE_TP(DomainConstants::GENRE_TP);
	///////////////////////////////
	Groupe::Groupe()
	{
		this->type(DomainConstants::GROUPE_TYPE);
		this->genre(DomainConstants::GENRE_TP);
		this->modified(false);
	}
	Groupe::Groupe(const Value &oMap) : DepSigleNamedItem(oMap) {
		this->type(DomainConstants::GROUPE_TYPE);
		this->modified(false);
	}
	Groupe::Groupe(const Departement &oDep) : DepSigleNamedItem(oDep) {
		this->type(DomainConstants::GROUPE_TYPE);
		this->genre(DomainConstants::GENRE_TP);
		this->modified(false);
	}
	Groupe::Groupe(const Groupe &other) : DepSigleNamedItem(other) {

	}
	Groupe & Groupe::operator=(const Groupe &other) {
		if (this != &other) {
			DepSigleNamedItem::operator=(other);
		}
		return (*this);
	}
	Groupe::~Groupe()
	{
	}
	std::string Groupe::genre(void) const {
		return this->get_string(DomainConstants::GENRE);
	}
	void Groupe::genre(const std::string &s) {
		std::string ss = to_upper(trim(s));
		if ((ss == GENRE_PROMO) || (ss == GENRE_TD) || (ss == GENRE_TP)) {
			this->set_string(DomainConstants::GENRE, ss);
		}
	}
	std::vector<std::string> Groupe::children_ids(void) const {
		std::vector<std::string> oRet;
		if (this->has_field(DomainConstants::CHILDRENIDS)) {
			Value *pVal = this->at(DomainConstants::CHILDRENIDS);
			if ((pVal != nullptr) && (pVal->is_array())) {
				Array *pAr = pVal->as_array();
				if (pAr != nullptr) {
					size_t n = pAr->size();
					for (size_t i = 0; i < n; ++i) {
						PValue vo = (*pAr)[i];
						Value *vv = vo.get();
						if ((vv != nullptr) && vv->is_string()) {
							std::string s = vv->as_string();
							if (!s.empty()) {
								oRet.push_back(s);
							}
						}// vv
					}// i
				}// pAr
			}// array
		}
		return (oRet);
	}
	bool Groupe::add_child(const Groupe &g) {
		std::string sid = g.id();
		std::string sg = g.genre();
		std::string xg = this->genre();
		if (sid.empty() || sg.empty() || xg.empty()) {
			return (false);
		}
		if (xg == DomainConstants::GENRE_TP) {
			return (false);
		}
		else if (xg == DomainConstants::GENRE_TD) {
			if (sg != DomainConstants::GENRE_TP) {
				return (false);
			}
		}
		else if (xg == DomainConstants::GENRE_PROMO) {
			if (sg != DomainConstants::GENRE_TD) {
				return (false);
			}
		}
		std::vector<std::string> vec = this->children_ids();
		for (auto it = vec.begin(); it != vec.end(); ++it) {
			std::string s = *it;
			if (s == sid) {
				return (false);
			}
		}
		vec.push_back(sid);
		this->children_ids(vec);
		return (true);
	}
	bool Groupe::remove_child(const Groupe &g) {
		std::string sid = g.id();
		if (sid.empty()) {
			return (false);
		}
		std::vector<std::string> vec = this->children_ids();
		bool bFound = false;
		for (auto it = vec.begin(); it != vec.end(); ++it) {
			std::string s = *it;
			if (s == sid) {
				vec.erase(it);
				bFound = true;
				break;
			}
		}
		if (bFound) {
			this->children_ids(vec);
			return (true);
		}
		return (false);
	}
	std::vector<PGroupe> Groupe::children(IDataManager &oMan) {
		std::vector<PGroupe> oRet;
		std::vector<std::string> vec = this->children_ids();
		if (!vec.empty()) {
			Value vr = oMan.read_docs_array(vec);
			if (vr.is_array()) {
				Array *pAr = vr.as_array();
				if (pAr != nullptr) {
					size_t n = pAr->size();
					for (size_t i = 0; i < n; ++i) {
						PValue vx = (*pAr)[i];
						Value *v = vx.get();
						if ((v != nullptr) && v->is_object()) {
							PGroupe ov = std::make_shared<Groupe>(*v);
							oRet.push_back(ov);
						}
					}// i
				}// pAr
			}// array
		}// not empty
		return oRet;
	}// children
	std::string Groupe::store_prefix(void) const {
		return DomainConstants::GROUPE_PREFIX;
	}
	bool Groupe::is_storeable(void) const {
		std::string s = this->genre();
		return ((!s.empty()) && DepSigleNamedItem::is_storeable());
	}
	void Groupe::children_ids(const std::vector<std::string> &ids) {
		std::string key = DomainConstants::CHILDRENIDS;
		if (this->has_field(key)) {
			Object *pObj = this->m_val.as_object();
			if (pObj != nullptr) {
				pObj->remove(key);
			}
		}
		Array *pAr = this->set_array(DomainConstants::CHILDRENIDS);
		if (pAr != nullptr) {
			for (auto it = ids.begin(); it != ids.end(); ++it) {
				std::string s = *it;
				if (!s.empty()) {
					PValue vv = std::make_shared<Value>(s);
					pAr->append_value(vv);
				}
			}// it
		}// pAr
	}
	///////////////////////////////////
}// namespace geninfo
