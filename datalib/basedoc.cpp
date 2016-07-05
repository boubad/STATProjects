#include "basedoc.h"
///////////////////////////
namespace info
{
	////////////////////////////////
	const std::string STRING_DELETED("_deleted");
	const std::string STRING_LOCAL_SEQ("_local_seq");
	const std::string STRING_CONFLICTS("_conflicts");
	const std::string STRING_DELETED_CONFLICTS("_deleted_conflicts");
	const std::string STRING_REVS_INFO("_revs_info");
	const std::string STRING_REVISIONS("_revisions");
	const std::string STRING_ATTACHMENTS("_attachments");
	const std::string STRING_ID("_id");
	const std::string STRING_REV("_rev");
	const std::string STRING_REV2("rev");
	const std::string STRING_STATUS("status");
	const std::string STRING_START("start");
	const std::string STRING_IDS("ids");
	const std::string STUB("stub");
	const std::string REVPOS("revpos");
	const std::string LENGTH("length");
	const std::string ENCODED_LENGTH("encoded_length");
	const std::string ENCODING("encoding");
	const std::string CONTENT_TYPE("content_type");
	const std::string DATA("data");
	const std::string DIGEST("digest");
	const std::string STRING_DELETED2("deleted");
	const std::string STRING_AVAILABLE("available");
	////////////////////////////////////////////
	AttachmentDesc::AttachmentDesc() :stub(false), revpos(0), length(0), encoded_length(0)
	{
	}
	AttachmentDesc::AttachmentDesc(const Value &oMap) : stub(false), revpos(0), length(0), encoded_length(0)
	{
		if (oMap.is_object())
		{
			Object *pObj = oMap.as_object();
			assert(pObj != nullptr);
			if (pObj->has_field(STUB))
			{
				Value *v = pObj->at(STUB);
				assert(v != nullptr);
				if (v->is_bool())
				{
					this->stub = v->as_bool();
				}
			}
			if (pObj->has_field(REVPOS))
			{
				Value *v = pObj->at(REVPOS);
				assert(v != nullptr);
				if (v->is_integer())
				{
					this->revpos = v->as_integer();
				}
			}
			if (pObj->has_field(LENGTH))
			{
				Value *v = pObj->at(LENGTH);
				assert(v != nullptr);
				if (v->is_integer())
				{
					this->length = v->as_integer();
				}
			}
			if (pObj->has_field(ENCODED_LENGTH))
			{
				Value *v = pObj->at(ENCODED_LENGTH);
				assert(v != nullptr);
				if (v->is_integer())
				{
					this->encoded_length = v->as_integer();
				}
			}
			if (pObj->has_field(ENCODING))
			{
				Value *v = pObj->at(ENCODING);
				assert(v != nullptr);
				if (v->is_string())
				{
					this->encoding = v->as_string();
				}
			}
			if (pObj->has_field(CONTENT_TYPE))
			{
				Value *v = pObj->at(CONTENT_TYPE);
				assert(v != nullptr);
				if (v->is_string())
				{
					this->content_type = v->as_string();
				}
			}
			if (pObj->has_field(DATA))
			{
				Value *v = pObj->at(DATA);
				assert(v != nullptr);
				if (v->is_string())
				{
					this->data = v->as_string();
				}
			}
			if (pObj->has_field(DIGEST))
			{
				Value *v = pObj->at(DIGEST);
				assert(v != nullptr);
				if (v->is_string())
				{
					this->digest = v->as_string();
				};
			}
		}// oMap
	}// AttachmentDesc
	AttachmentDesc::AttachmentDesc(const AttachmentDesc &other) :stub(other.stub), revpos(other.revpos), length(other.length), encoded_length(other.encoded_length),
		encoding(other.encoding), content_type(other.content_type), data(other.data), digest(other.digest)
	{
	}
	AttachmentDesc & AttachmentDesc::operator=(const AttachmentDesc &other)
	{
		if (this != &other)
		{
			this->stub = other.stub;
			this->revpos = other.revpos;
			this->length = other.length;
			this->encoded_length = other.encoded_length;
			this->encoding = other.encoding;
			this->content_type = other.content_type;
			this->data = other.data;
			this->digest = other.digest;
		}
		return *this;
	}
	AttachmentDesc::~AttachmentDesc()
	{
	}
	///////////////////////////////////////
	RevisionsData::RevisionsData() :_start(0)
	{
	}
	RevisionsData::RevisionsData(const Value &oMap) : _start(0)
	{
		if (oMap.is_object())
		{
			Object *pObj = oMap.as_object();
			assert(pObj != nullptr);
			if (pObj->has_field(STRING_START))
			{
				Value *v = pObj->at(STRING_START);
				assert(v != nullptr);
				if (v->is_integer())
				{
					this->_start = v->as_integer();
				}
			}
			if (pObj->has_field(STRING_IDS))
			{
				Value *v = pObj->at(STRING_IDS);
				assert(v != nullptr);
				if (v->is_array())
				{
					Array *pAr = v->as_array();
					assert(pAr != nullptr);
					std::vector<std::string> &vec = this->_ids;
					size_t n = pAr->size();
					for (size_t i = 0; i < n; ++i)
					{
						PValue vx = (*pAr)[i];
						Value *p = vx.get();
						assert(p != nullptr);
						if (p->is_string())
						{
							std::string s = p->as_string();
							if (!s.empty())
							{
								vec.push_back(s);
							}
						}
					}// i
				}
			}
		}// oMap
	}
	RevisionsData::RevisionsData(const RevisionsData &other) :_start(other._start),
		_ids(other._ids)
	{

	}
	RevisionsData & RevisionsData::operator=(const RevisionsData &other)
	{
		if (this != &other)
		{
			this->_start = other._start;
			this->_ids = other._ids;
		}
		return *this;
	}
	RevisionsData::~RevisionsData()
	{

	}
	int  RevisionsData::start(void) const
	{
		return this->_start;
	}
	const std::vector<std::string> & RevisionsData::ids(void) const
	{
		return this->_ids;
	}
	/////////////////////////////////////
	RevisionInfo::RevisionInfo()
	{

	}
	RevisionInfo::RevisionInfo(const Value &oMap)
	{
		if (oMap.is_object())
		{
			Object *pObj = oMap.as_object();
			assert(pObj != nullptr);
			if (pObj->has_field(STRING_REV2))
			{
				Value *v = pObj->at(STRING_REV2);
				assert(v != nullptr);
				if (v->is_string())
				{
					this->_rev = v->as_string();
				}
			}
			if (pObj->has_field(STRING_STATUS))
			{
				Value *v = pObj->at(STRING_STATUS);
				assert(v != nullptr);
				if (v->is_string())
				{
					this->_status = v->as_string();
				}
			}
		}// oMap
	}
	RevisionInfo::RevisionInfo(const RevisionInfo &other) :_rev(other._rev),
		_status(other._status)
	{

	}
	RevisionInfo & RevisionInfo::operator=(const RevisionInfo &other)
	{
		if (this != &other)
		{
			this->_rev = other._rev;
			this->_status = other._status;
		}
		return *this;
	}
	RevisionInfo::~RevisionInfo()
	{

	}
	const std::string & RevisionInfo::rev(void) const
	{
		return this->_rev;
	}
	const std::string & RevisionInfo::status(void) const
	{
		return this->_status;
	}
	bool RevisionInfo::is_available(void) const
	{
		return (!this->_status.empty()) && (this->_status == STRING_AVAILABLE);
	}
	bool RevisionInfo::is_deleted(void) const
	{
		return (!this->_status.empty()) && (this->_status == STRING_DELETED2);
	}
	//////////////////////////////////
	BaseDoc::BaseDoc():m_val(Value::create_object_value())
	{
		
	}
	BaseDoc::BaseDoc(const Value &oMap) :m_val(oMap)
	{

	}
	BaseDoc & BaseDoc::operator=(const BaseDoc &other)
	{
		if (this != &other)
		{
			this->m_val = other.m_val;
		}
		return (*this);
	}
	BaseDoc::~BaseDoc()
	{
		//dtor
	}
	Value *BaseDoc::at(const std::string &key) const
	{
		Value *pRet = nullptr;
		if (!key.empty())
		{
			if (this->m_val.is_object())
			{
				Object *pObj = this->m_val.as_object();
				if ((pObj != nullptr) && pObj->contains(key))
				{
					pRet = pObj->at(key);
				}
			}// map
		}// s
		return pRet;
	}
	bool BaseDoc::has_id(void) const
	{
		std::string s = this->id();
		return (!s.empty());
	}
	bool BaseDoc::has_rev(void) const
	{
		std::string s = this->rev();
		return (!s.empty());
	}
	void BaseDoc::id(const std::string &s)
	{
		this->set_string(STRING_ID, s);
	}
	void BaseDoc::rev(const std::string &s)
	{
		this->set_string(STRING_REV, s);
	}
	bool BaseDoc::has_field(const std::string &s) const
	{
		return (this->at(s) != nullptr);
	}
	bool BaseDoc::is_empty(void) const
	{
		bool bRet = false;
		if (this->m_val.is_object())
		{
			Object *p = this->m_val.as_object();
			bRet = ((p != nullptr) && (p->is_empty()));
		}
		return bRet;
	}
	bool BaseDoc::contains(const std::string &key) const
	{
		return (this->at(key) != nullptr);
	}
	bool BaseDoc::get_bool(const std::string &key) const
	{
		bool bRet = false;
		Value *p = this->at(key);
		if (p != nullptr)
		{
			bRet = p->as_bool();
		}
		return bRet;
	}
	int BaseDoc::get_int(const std::string &key) const
	{
		int bRet = 0;
		Value *p = this->at(key);
		if (p != nullptr)
		{
			bRet = p->as_integer();
		}
		return bRet;
	}
	double BaseDoc::get_double(const std::string &key) const
	{
		double bRet = 0.0;
		Value *p = this->at(key);
		if (p != nullptr)
		{
			bRet = p->as_double();
		}
		return bRet;
	}
	std::string BaseDoc::get_string(const std::string &key) const
	{
		std::string bRet;
		Value *p = this->at(key);
		if (p != nullptr)
		{
			bRet = p->as_string();
		}
		return bRet;
	}
	Array *BaseDoc::get_array(const std::string &key) const
	{
		Array *pRet = nullptr;
		if (!key.empty())
		{
			if (this->m_val.is_object())
			{
				Object *pObj = this->m_val.as_object();
				if (pObj != nullptr)
				{
					pRet = pObj->get_array(key);
				}
			}// map
		}// s
		return pRet;
	}
	Object *BaseDoc::get_object(const std::string &key) const
	{
		Object *pRet = nullptr;
		if (!key.empty())
		{
			if (this->m_val.is_object())
			{
				Object *pObj = this->m_val.as_object();
				if (pObj != nullptr)
				{
					pRet = pObj->get_object(key);
				}
			}// map
		}// s
		return pRet;
	}
	void BaseDoc::remove(const std::string &key)
	{
		if (!key.empty())
		{
			if (this->m_val.is_object())
			{
				Object *pObj = this->m_val.as_object();
				if (pObj != nullptr)
				{
					pObj->remove(key);
				}
			}// map
		}// s
	}
	std::set<std::string> BaseDoc::keys(void) const
	{
		std::set<std::string> oRet;
		if (this->m_val.is_object())
		{
			Object *pObj = this->m_val.as_object();
			if (pObj != nullptr)
			{
				oRet = pObj->keys();
			}
		}// map
		return oRet;
	}
	void BaseDoc::set_bool(const std::string &key, bool b)
	{
		if (!key.empty())
		{
			if (this->m_val.is_object())
			{
				Object *pObj = this->m_val.as_object();
				if (pObj != nullptr)
				{
					pObj->set_bool(key, b);
				}
			}// map
		}// s
	}
	void BaseDoc::set_int(const std::string &key, int b)
	{
		if (!key.empty())
		{
			if (this->m_val.is_object())
			{
				Object *pObj = this->m_val.as_object();
				if (pObj != nullptr)
				{
					pObj->set_int(key, b);
				}
			}// map
		}// s
	}
	void BaseDoc::set_double(const std::string &key, double b)
	{
		if (!key.empty())
		{
			if (this->m_val.is_object())
			{
				Object *pObj = this->m_val.as_object();
				if (pObj != nullptr)
				{
					pObj->set_double(key, b);
				}
			}// map
		}// s
	}
	void BaseDoc::set_string(const std::string &key, std::string b)
	{
		if (!key.empty())
		{
			if (this->m_val.is_object())
			{
				Object *pObj = this->m_val.as_object();
				if (pObj != nullptr)
				{
					pObj->set_string(key, b);
				}
			}// map
		}// s
	}
	Array *BaseDoc::set_array(const std::string &key)
	{
		Array *pRet = nullptr;
		if (!key.empty())
		{
			if (this->m_val.is_object())
			{
				Object *pObj = this->m_val.as_object();
				if (pObj != nullptr)
				{
					pRet = pObj->set_array(key);
				}
			}// map
		}// s
		return pRet;
	}
	Object *BaseDoc::set_object(const std::string &key)
	{
		Object* pRet = nullptr;
		if (!key.empty())
		{
			if (this->m_val.is_object())
			{
				Object *pObj = this->m_val.as_object();
				if (pObj != nullptr)
				{
					pRet = pObj->set_object(key);
				}
			}// map
		}// s
		return pRet;
	}
	bool BaseDoc::deleted(void) const
	{
		return this->get_bool(STRING_DELETED);
	}
	int BaseDoc::local_seq(void) const
	{
		return this->get_int(STRING_LOCAL_SEQ);
	}
	std::string  BaseDoc::id(void) const
	{
		return this->get_string(STRING_ID);
	}
	std::string  BaseDoc::rev(void) const
	{
		return this->get_string(STRING_REV);
	}
	std::vector<std::string>  BaseDoc::conflicts(void) const
	{
		std::vector<std::string> vec;
		Value *pval = this->at(STRING_CONFLICTS);
		if ((pval != nullptr) && pval->is_array())
		{
			Array *pAr = pval->as_array();
			assert(pAr != nullptr);
			size_t n = pAr->size();
			for (size_t i = 0; i < n; ++i)
			{
				PValue vv = (*pAr)[i];
				Value *v = vv.get();
				assert(v != nullptr);
				if (v->is_string())
				{
					std::string s = v->as_string();
					if (!s.empty())
					{
						vec.push_back(s);
					}
				}
			}// i
		}// pval
		return vec;
	}
	std::vector<std::string>  BaseDoc::deleted_conflicts(void) const
	{
		std::vector<std::string> vec;
		Value *pval = this->at(STRING_DELETED_CONFLICTS);
		if ((pval != nullptr) && pval->is_array())
		{
			Array *pAr = pval->as_array();
			assert(pAr != nullptr);
			size_t n = pAr->size();
			for (size_t i = 0; i < n; ++i)
			{
				PValue vv = (*pAr)[i];
				Value *v = vv.get();
				assert(v != nullptr);
				if (v->is_string())
				{
					std::string s = v->as_string();
					if (!s.empty())
					{
						vec.push_back(s);
					}
				}
			}// i
		}// pval
		return vec;
	}
	std::vector<RevisionInfo>  BaseDoc::revs_info(void) const
	{
		std::vector<RevisionInfo> vec;
		Value *pval = this->at(STRING_REVS_INFO);
		if ((pval != nullptr) && pval->is_array())
		{
			Array *pAr = pval->as_array();
			assert(pAr != nullptr);
			size_t n = pAr->size();
			for (size_t i = 0; i < n; ++i)
			{
				PValue vv = (*pAr)[i];
				Value *v = vv.get();
				assert(v != nullptr);
				if (v->is_object())
				{
					RevisionInfo info(*v);
					vec.push_back(info);
				}
			}// i
		}// pval
		return vec;
	}
	RevisionsData  BaseDoc::revisions(void) const
	{
		RevisionsData oRet;
		Value *pval = this->at(STRING_REVISIONS);
		if ((pval != nullptr) && pval->is_object())
		{
			oRet = RevisionsData(*pval);
		}
		return oRet;
	}
	std::map<std::string, AttachmentDesc>  BaseDoc::attachments(void) const
	{
		std::map<std::string, AttachmentDesc> oRet;
		Value *pval = this->at(STRING_ATTACHMENTS);
		if ((pval != nullptr) && pval->is_object())
		{
			Object *pObj = pval->as_object();
			if (pObj != nullptr)
			{
				std::set<std::string> keys = pObj->keys();
				for (auto it = keys.begin(); it != keys.end(); ++it)
				{
					std::string name = *it;
					Value *vx = pObj->at(name);
					if ((vx != nullptr) && vx->is_object())
					{
						AttachmentDesc desc(*vx);
						oRet[name] = desc;
					}
				}// it
			}// pObj
		}// object
		return oRet;
	}
	std::ostream & BaseDoc::write_to(std::ostream &os) const
	{
		this->m_val.write_to(os);
		return os;
	}
	std::string BaseDoc::to_string(void) const
	{
		std::stringstream os;
		this->write_to(os);
		return os.str();
	}
	//////////////////////////////////////
}
