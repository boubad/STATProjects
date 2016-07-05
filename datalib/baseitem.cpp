#include "baseitem.h"
#include "idatamanager.h"
#include "domainconstants.h"
#include <boost/algorithm/string.hpp>
////////////////////////////
namespace info {
	//////////////////////////////////////
	const std::string STRING_OK("ok");
	const std::string STRING_REV2("rev");
	///////////////////////////////////
	std::string BaseItem::trim(const std::string &s) {
		return boost::trim_copy(s);
	}
	std::string BaseItem::to_lower(const std::string &s) {
		return boost::to_lower_copy(s);
	}
	std::string BaseItem::to_upper(const std::string &s) {
		return boost::to_upper_copy(s);
	}
	std::string BaseItem::format_name(const std::string &s) {
		std::string ss = trim(s);
		size_t n = ss.length();
		if (n < 2) {
			return to_upper(ss);
		}
		else {
			return (to_upper(ss.substr(0, 1)) + ss.substr(1, n - 1));
		}
	}
	/////////////////////////////////
	BaseItem::BaseItem():m_modified(false),m_selected(false) {

	}
	BaseItem::BaseItem(const Value &oMap) :BaseDoc(oMap), m_modified(false), m_selected(false) {

	}
	BaseItem::BaseItem(const BaseItem &other) : BaseDoc(other), m_modified(other.m_modified), m_selected(other.m_selected) {

	}
	BaseItem &  BaseItem::operator=(const BaseItem &other) {
		if (this != &other) {
			BaseDoc::operator=(other);
			this->m_modified = other.m_modified;
			this->m_selected = other.m_selected;
		}
		return (*this);
	}
	BaseItem::~BaseItem() {

	}
	bool BaseItem::modified(void) const {
		return (this->m_modified);
	}
	void BaseItem::modified(bool b) {
		this->m_modified = b;
	}
	bool BaseItem::selected(void) const {
		return (this->m_selected);
	}
	void BaseItem::selected(bool b) {
		this->m_selected = b;
	}
	void BaseItem::set_bool(const std::string &key, bool b) {
		bool bOld = this->get_bool(key);
		if (bOld != b) {
			BaseDoc::set_bool(key, b);
			this->modified(true);
		}
	}
	void BaseItem::set_int(const std::string &key, int b) {
		int bOld = this->get_int(key);
		if (bOld != b) {
			BaseDoc::set_int(key, b);
			this->modified(true);
		}
	}
	void BaseItem::set_double(const std::string &key, double b) {
		double bOld = this->get_double(key);
		if (bOld != b) {
			BaseDoc::set_double(key, b);
			this->modified(true);
		}
	}
	void BaseItem::set_string(const std::string &key, std::string b) {
		std::string bOld = this->get_string(key);
		if (bOld != b) {
			BaseDoc::set_string(key, b);
			this->modified(true);
		}
	}
	std::string  BaseItem::status(void) const {
		return this->get_string(DomainConstants::STATUS);
	}
	void  BaseItem::status(const std::string &s) {
		this->set_string(DomainConstants::STATUS, to_upper(trim(s)));
	}
	std::string  BaseItem::description(void) const {
		return this->get_string(DomainConstants::DESCRIPTION);
	}
	void  BaseItem::description(const std::string &s) {
		this->set_string(DomainConstants::DESCRIPTION, trim(s));
	}
	std::string  BaseItem::store_prefix(void) const {
		return (std::string());
	}
	std::string  BaseItem::start_key(void) const {
		return (this->store_prefix());
	}
	std::string  BaseItem::create_id(void) const {
		return (this->start_key());
	}
	bool  BaseItem::is_storeable(void) const {
		std::string s1 = this->type();
		std::string s2 = this->store_prefix();
		return ((!s1.empty()) && (!s2.empty()));
	}
	std::string BaseItem::text(void) const {
		return std::string();
	}
	std::string  BaseItem::type(void) const {
		return this->get_string(DomainConstants::TYPE);
	}
	void BaseItem::type(const std::string &s) {
		this->set_string(DomainConstants::TYPE, s);
	}
	std::string  BaseItem::end_key(void) const {
		std::string s1 = this->start_key();
		s1 += std::string("zzzzzz");
		return s1;
	}
	void  BaseItem::check_id(void) {
		std::string s = this->id();
		if (s.empty()) {
			this->id(this->create_id());
		}
	}
	bool  BaseItem::load(IDataManager &oMan) {
		bool bRet = false;
		this->check_id();
		std::string id = this->id();
		if (!id.empty()) {
			Value val = oMan.read_doc(id, true);
			if (val.is_object()) {
				this->m_val = val;
				this->modified(false);
				bRet = true;
			}
		}
		return bRet;
	}
	bool  BaseItem::save(IDataManager &oMan) {
		bool bRet = false;
		this->check_id();
		if (!this->has_id()) {
			return (false);
		}
		if (!this->is_storeable()) {
			return (false);
		}
		Value vr = oMan.insert_doc(this->value());
		if (vr.is_object()) {
			Object  *pObj = vr.as_object();
			if ((pObj != nullptr) && pObj->has_field(STRING_OK)) {
				if ((bRet = pObj->get_bool(STRING_OK)) == true) {
					this->rev(pObj->get_string(STRING_REV2));
					this->modified(false);
				}
			}// obj
		}// vr
		return bRet;
	}
	bool  BaseItem::remove(IDataManager &oMan) {
		bool bRet = false;
		this->check_id();
		std::string id = this->id();
		if (!id.empty()) {
			Value vr = oMan.remove_doc(this->value());
			if (vr.is_object()) {
				Object  *pObj = vr.as_object();
				if ((pObj != nullptr) && pObj->has_field(STRING_OK)) {
					if ((bRet = pObj->get_bool(STRING_OK)) == true) {
						this->rev(pObj->get_string(STRING_REV2));
						Object *pObj = this->m_val.as_object();
						if (pObj != nullptr) {
							pObj->set_bool(DomainConstants::DELETED, true);
						}
					}
				}// obj
			}// vr
		}
		return bRet;
	}

	/////////////////////////////////
}// namespace geninfo
////////////////////////////
