/////////////////////////////
#include "value.h"
#include <boost/algorithm/string.hpp>
#include <boost/any.hpp>
#include <sstream>
//////////////////////////////////
namespace info
{
	using namespace std;
	using namespace boost;
	//////////////////////////////////////
	extern std::string trim(const std::string &s)
	{
		return boost::trim_copy(s);
	}
	extern std::string to_lower(const std::string &s)
	{
		return boost::to_lower_copy(s);
	}
	extern std::string to_upper(const std::string &s)
	{
		return boost::to_upper_copy(s);
	}
	///////////////////////
	PObject Value::create_object(void)
	{
		return std::make_shared<Object>();
	}
	PArray Value::create_array(void)
	{
		return std::make_shared<Array>();
	}
	Value Value::create_object_value(void) {
		PObject o = create_object();
		return Value(o);
	}
	/////////////////
	Value::Value() :m_type(value_type::null_type)
	{
		//ctor
	}
	Value::Value(bool b) : m_type(value_type::boolean_type), 
m_data(make_shared<any>(b))
	{
	}
	Value::Value(int b) : m_type(value_type::integer_type), 
m_data(make_shared<any>(b))
	{
	}
	Value::Value(unsigned int b) : m_type(value_type::integer_type), 
m_data(make_shared<any>((int)b))
	{
	}
	Value::Value(float b) : m_type(value_type::double_type), 
m_data(make_shared<any>((double)b))
	{
	}
	Value::Value(double b) : m_type(value_type::double_type), 
m_data(make_shared<any>(b))
	{
	}
	Value::Value(std::string b) : m_type(value_type::string_type), 
m_data(make_shared<any>(b))
	{
	}
	Value::Value(PArray b) : m_type(value_type::array_type), 
m_data(make_shared<any>(b))
	{
	}
	Value::Value(PObject b) : m_type(value_type::object_type), 
m_data(make_shared<any>(b))
	{
	}
	Value::Value(const Value &other) : m_type(other.m_type), 
m_data(other.m_data)
	{
		//ctor
	}
	Value & Value::operator=(const Value & other)
	{
		if (this != &other)
		{
			this->m_type = other.m_type;
			this->m_data = other.m_data;
		}
		return (*this);
	}
	Value::~Value()
	{
		//dtor
	}
	value_type Value::type(void) const {
		return this->m_type;
	}
	bool Value::is_null(void) const
	{
		return (m_type == value_type::null_type);
	}
	bool Value::is_bool(void) const
	{
		return (m_type == value_type::boolean_type);
	}
	bool Value::is_integer(void) const
	{
		return (m_type == value_type::integer_type);
	}
	bool Value::is_double(void) const
	{
		return (m_type == value_type::double_type);
	}
	bool Value::is_string(void) const
	{
		return (m_type == value_type::string_type);
	}
	bool Value::is_array(void) const
	{
		return (m_type == value_type::array_type);
	}
	bool Value::is_object(void) const
	{
		return (m_type == value_type::object_type);
	}
	//
	bool Value::as_bool(void) const
	{
		bool bRet = false;
		try
		{
			const boost::any *p = this->m_data.get();
			if ((p != nullptr) && (!p->empty()))
			{
				bRet = boost::any_cast<bool>(*p);
			}
		}
		catch (const boost::bad_any_cast &) {}
		return bRet;
	}
	int Value::as_integer(void) const
	{
		int bRet = 0;
		try
		{
			const boost::any *p = this->m_data.get();
			if ((p != nullptr) && (!p->empty()))
			{
				if (this->is_double())
				{
					bRet = (int)boost::any_cast<double>(*p);
				}
				else
				{
					bRet = boost::any_cast<int>(*p);
				}
			}
		}
		catch (const boost::bad_any_cast &) {}
		return bRet;
	}
	double Value::as_double(void) const
	{
		double bRet = 0.0;
		try
		{
			const boost::any *p = this->m_data.get();
			if ((p != nullptr) && (!p->empty()))
			{
				if (this->is_integer())
				{
					bRet = (double)boost::any_cast<int>(*p);
				}
				else
				{
					bRet = boost::any_cast<double>(*p);
				}

			}
		}
		catch (const boost::bad_any_cast &) {}
		return bRet;
	}
	std::string Value::as_string(void) const
	{
		std::string bRet;
		try
		{
			const boost::any *p = this->m_data.get();
			if ((p != nullptr) && (!p->empty()))
			{
				bRet = boost::any_cast<std::string>(*p);
			}
		}
		catch (const boost::bad_any_cast &) {}
		return bRet;
	}
	Object *Value::as_object(void) const
	{
		Object *bRet = nullptr;
		try
		{
			const boost::any *p = this->m_data.get();
			if ((p != nullptr) && (!p->empty()))
			{
				PObject xRet = boost::any_cast<PObject>(*p);
				bRet = xRet.get();
			}
		}
		catch (const boost::bad_any_cast &) {}
		return bRet;
	}
	Array *Value::as_array(void) const
	{
		Array *bRet = nullptr;
		try
		{
			const boost::any *p = this->m_data.get();
			if ((p != nullptr) && (!p->empty()))
			{
				PArray xRet = boost::any_cast<PArray>(*p);
				bRet = xRet.get();
			}
		}
		catch (const boost::bad_any_cast &) {}
		return bRet;
	}
	//
	std::ostream & Value::write_to(std::ostream &os) const
	{
		switch (this->m_type)
		{
		case value_type::null_type:
		{
			os << "null";
		}
		break;
		case value_type::array_type:
		{
			Array *pAr = this->as_array();
			if (pAr != nullptr)
			{
				pAr->write_to(os);
			}
		}
		break;
		case value_type::object_type:
		{
			Object *pObj = this->as_object();
			if (pObj != nullptr)
			{
				pObj->write_to(os);
			}
		}
		break;
		case value_type::string_type:
		{
			std::string s = this->as_string();
			os << "\"" << s << "\"";
		}
		break;
		case value_type::boolean_type:
		{
			bool b = this->as_bool();
			os << ((b) ? "true" : "false");
		}
		break;
		case value_type::double_type:
			os << this->as_double();
			break;
		case value_type::integer_type:
			os << this->as_integer();
			break;
		default:
			break;
		}// type
		return os;
	}// write_to
	std::string Value::to_string(void) const
	{
		std::stringstream os;
		this->write_to(os);
		return os.str();
	}
	/////////////////////////////////////
	Array::Array()
	{
	}
	Array::Array(const std::vector<PValue> &oVec) :m_vec(oVec)
	{
	}
	Array::Array(const Array &other) : m_vec(other.m_vec)
	{
	}
	Array & Array::operator=(const Array &other)
	{
		if (this != &other)
		{
			this->m_vec = other.m_vec;
		}
		return (*this);
	}
	Array::~Array()
	{
	}
	bool Array::is_empty(void) const
	{
		return (this->m_vec.empty());
	}
	size_t Array::size(void) const
	{
		return (this->m_vec.size());
	}
	void Array::clear(void)
	{
		this->m_vec.clear();
	}
	const PValue & Array::operator[](size_t i) const
	{
		return (this->m_vec[i]);
	}

	void Array::append_bool(bool b)
	{
		this->append(std::make_shared<Value>(b));
	}
	void Array::append_int(int b)
	{
		this->append(std::make_shared<Value>(b));
	}
	void Array::append_uint(unsigned int b)
	{
		this->append(std::make_shared<Value>(b));
	}
	void Array::append_float(float b)
	{
		this->append(std::make_shared<Value>(b));
	}
	void Array::append_double(double b)
	{
		this->append(std::make_shared<Value>(b));
	}
	void Array::append_string(std::string b)
	{
		this->append(std::make_shared<Value>(b));
	}
	void Array::append_value(PValue v) {
		this->append(v);
	}
	void Array::append_value(const Value &v) {
		if (!v.is_null()) {
			PValue pp = std::make_shared <Value>(v);
			this->append(pp);
		}
	}
	void Array::append_object(PObject v) {
		if (v.get() != nullptr) {
			this->append(std::make_shared<Value>(v));
		}
	}
	void  Array::append_array(PArray v) {
		if (v.get() != nullptr) {
			this->append(std::make_shared<Value>(v));
		}
	}
	Array * Array::append_array()
	{
		PArray b = std::make_shared<Array>();
		this->append(std::make_shared<Value>(b));
		return b.get();
	}
	Object * Array::append_object()
	{
		PObject b = std::make_shared<Object>();
		this->append(std::make_shared<Value>(b));
		return b.get();
	}

	PValue & Array::operator[](size_t i)
	{
		return (this->m_vec[i]);
	}
	void Array::push_back(PValue b)
	{
		if (b.get() != nullptr)
		{
			this->m_vec.push_back(b);
		}
	}
	void Array::append(PValue b)
	{
		if (b.get() != nullptr)
		{
			this->m_vec.push_back(b);
		}
	}
	std::ostream & Array::write_to(std::ostream &os) const
	{
		os << "[";
		auto istart = this->m_vec.begin();
		auto iend = this->m_vec.end();
		for (auto it = istart; it != iend; ++it)
		{
			if (it != istart)
			{
				os << ",";
			}
			PValue vv = *it;
			auto *p = vv.get();
			if (p != nullptr)
			{
				p->write_to(os);
			}
		}// it
		os << "]";
		return os;
	}
	std::string Array::to_string(void) const
	{
		std::stringstream os;
		this->write_to(os);
		return os.str();
	}
	/////////////////////////////////////////
	Object::Object()
	{
	}
	Object::Object(const std::map<std::string, PValue> &oMap) :m_map(oMap)
	{
	}
	Object::Object(const Object &other) : m_map(other.m_map)
	{
	}
	Object & Object::operator=(const Object & other)
	{
		if (this != &other)
		{
			this->m_map = other.m_map;
		}
		return (*this);
	}
	Object::~Object()
	{
	}
	bool Object::is_empty(void) const
	{
		return (this->m_map.empty());
	}
	bool Object::contains(const std::string &key) const
	{
		return (this->m_map.find(key) != this->m_map.end());
	}
	bool Object::has_field(const std::string &key) const
	{
		return (this->m_map.find(key) != this->m_map.end());
	}
	Value *Object::at(const std::string &key) const
	{
		Value *pRet = nullptr;
		auto it = this->m_map.find(key);
		if (it != this->m_map.end())
		{
			auto oRet = (*it).second;
			pRet = oRet.get();
		}
		return pRet;
	}
	bool Object::get_bool(const std::string &key) const
	{
		bool bRet = false;
		Value *p = this->at(key);
		if ((p != nullptr) && p->is_bool())
		{
			bRet = p->as_bool();
		}
		return (bRet);
	}
	int Object::get_int(const std::string &key) const
	{
		int bRet = 0;
		Value *p = this->at(key);
		if ((p != nullptr) && p->is_integer())
		{
			bRet = p->as_integer();
		}
		return (bRet);
	}
	double Object::get_double(const std::string &key) const
	{
		double bRet = false;
		Value *p = this->at(key);
		if ((p != nullptr) && p->is_double())
		{
			bRet = p->as_double();
		}
		return (bRet);
	}
	std::string Object::get_string(const std::string &key) const
	{
		std::string bRet;
		Value *p = this->at(key);
		if ((p != nullptr) && p->is_string())
		{
			bRet = p->as_string();
		}
		return (bRet);
	}
	Array *Object::get_array(const std::string &key) const
	{
		Array *bRet = nullptr;
		Value *p = this->at(key);
		if ((p != nullptr) && p->is_array())
		{
			bRet = p->as_array();
		}
		return (bRet);
	}
	Object *Object::get_object(const std::string &key) const
	{
		Object *bRet = nullptr;
		Value *p = this->at(key);
		if ((p != nullptr) && p->is_object())
		{
			bRet = p->as_object();
		}
		return (bRet);
	}
	void Object::remove(const std::string &key)
	{
		auto it = this->m_map.find(key);
		if (it != this->m_map.end())
		{
			this->m_map.erase(it);
		}
	}
	std::set<std::string> Object::keys(void) const
	{
		std::set<std::string> oRet;
		auto iend = this->m_map.end();
		for (auto it = this->m_map.begin(); it != iend; ++it)
		{
			oRet.insert((*it).first);
		}
		return oRet;
	}
	void Object::set_bool(const std::string &key, bool b)
	{
		PValue v = std::make_shared<Value>(b);
		this->set(key, v);
	}
	void Object::set_int(const std::string &key, int b)
	{
		PValue v = std::make_shared<Value>(b);
		this->set(key, v);
	}
	void Object::set_double(const std::string &key, double b)
	{
		PValue v = std::make_shared<Value>(b);
		this->set(key, v);
	}
	void Object::set_string(const std::string &key, std::string b)
	{
		PValue v = std::make_shared<Value>(b);
		this->set(key, v);
	}
	void Object::set_value(const std::string &key, const Value &b) {
		PValue v = std::make_shared<Value>(b);
		this->set(key, v);
	}
	Array *Object::set_array(const std::string &key)
	{
		Array *pRet = nullptr;
		auto it = this->m_map.find(key);
		if (it != this->m_map.end())
		{
			auto v = (*it).second;
			Value *pv = v.get();
			if (pv != nullptr)
			{
				pRet = pv->as_array();
			}
		}
		else
		{
			PArray pAr = std::make_shared<Array>();
			PValue v = std::make_shared<Value>(pAr);
			this->m_map[key] = v;
			pRet = pAr.get();
		}
		return pRet;
	}
	Object *Object::set_object(const std::string &key)
	{
		Object *pRet = nullptr;
		auto it = this->m_map.find(key);
		if (it != this->m_map.end())
		{
			auto v = (*it).second;
			Value *pv = v.get();
			if (pv != nullptr)
			{
				pRet = pv->as_object();
			}
		}
		else
		{
			PObject pObj = std::make_shared<Object>();
			PValue v = std::make_shared<Value>(pObj);
			this->m_map[key] = v;
			pRet = pObj.get();
		}
		return pRet;
	}
	void Object::set(const std::string &key, PValue v)
	{
		if ((!key.empty()) && (v.get() != nullptr))
		{
			this->m_map[key] = v;
		}
	}
	void Object::set_array(const std::string &key, PArray b)
	{
		PValue v = std::make_shared<Value>(b);
		this->set(key, v);
	}
	void Object::set_object(const std::string &key, PObject b)
	{
		PValue v = std::make_shared<Value>(b);
		this->set(key, v);
	}
	std::ostream & Object::write_to(std::ostream &os) const
	{
		os << "{";
		auto istart = this->m_map.begin();
		auto iend = this->m_map.end();
		for (auto it = istart; it != iend; ++it)
		{
			if (it != istart)
			{
				os << ",";
			}
			std::string key = (*it).first;
			os << "\"" << key << "\":";
			PValue vv = (*it).second;
			auto *p = vv.get();
			if (p != nullptr)
			{
				p->write_to(os);
			}
		}// it
		os << "}";
		return os;
	}
	std::string Object::to_string(void) const
	{
		std::stringstream os;
		this->write_to(os);
		return os.str();
	}
	/////////////////////////////////////
}// namespace geninfo
