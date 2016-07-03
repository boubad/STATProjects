#pragma once
#ifndef __VALUE_H__
#define __VALUE_H__
///////////////////////////
#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <set>
/////////////////////////
namespace boost
{
	class any;
}
namespace info
{
	//////////////////////////////
	enum class value_type { null_type, boolean_type, integer_type, 
double_type, string_type, array_type, object_type };
	/////////////////////////////
	extern std::string trim(const std::string &s);
	extern std::string to_lower(const std::string &s);
	extern std::string to_upper(const std::string &s);
	/////////////////////////////
	class Value;
	class Object;
	class Array;
	////////////////////////////
	typedef std::shared_ptr<Value> PValue;
	typedef std::shared_ptr<Object> PObject;
	typedef std::shared_ptr<Array> PArray;
	///////////////////////////////
	class Value
	{
	public:
		static PObject create_object(void);
		static PArray create_array(void);
		static Value create_object_value(void);
	public:
		Value();
		explicit Value(bool b);
		explicit Value(int b);
		explicit Value(unsigned int b);
		explicit Value(float b);
		explicit Value(double b);
		explicit Value(std::string b);
		explicit Value(PArray b);
		explicit Value(PObject b);
		Value(const Value &other);
		Value & operator=(const Value &other);
		virtual ~Value();
	public:
		value_type type(void) const;
		bool is_null(void) const;
		bool is_bool(void) const;
		bool is_integer(void) const;
		bool is_double(void) const;
		bool is_string(void) const;
		bool is_array(void) const;
		bool is_object(void) const;
		bool as_bool(void) const;
		int as_integer(void) const;
		double as_double(void) const;
		std::string as_string(void) const;
		Object *as_object(void) const;
		Array *as_array(void) const;
		//
		std::ostream & write_to(std::ostream &os) const;
		std::string to_string(void) const;
	private:
		value_type m_type;
		std::shared_ptr<boost::any> m_data;
	}; // class Value
	   ///////////////////////////
	class Array
	{
	public:
		typedef std::vector<PValue> values_vector;
	public:
		Array();
		Array(const std::vector<PValue> &oVec);
		Array(const Array &other);
		Array & operator=(const Array &other);
		virtual ~Array();
		operator const std::vector<PValue>&() const
		{
			return (this->m_vec);
		}
		operator std::vector<PValue>&()
		{
			return (this->m_vec);
		}
	public:
		bool is_empty(void) const;
		size_t size(void) const;
		void clear(void);
		const PValue & operator[](size_t i) const;
		PValue & operator[](size_t i);
		void append_bool(bool b);
		void append_int(int b);
		void append_uint(unsigned int b);
		void append_float(float b);
		void append_double(double b);
		void append_string(std::string b);
		void append_value(PValue v);
		void append_value(const Value &v);
		void append_object(PObject v);
		void append_array(PArray v);
		Array * append_array();
		Object * append_object();
		//
		std::ostream & write_to(std::ostream &os) const;
		std::string to_string(void) const;
	protected:
		void push_back(PValue b);
		void append(PValue b);
	private:
		values_vector m_vec;
	}; // class Array
	   //////////////////////////////////
	class Object
	{
	public:
		Object();
		Object(const std::map<std::string, PValue> &oMap);
		Object(const Object &other);
		Object & operator=(const Object & other);
		virtual ~Object();
		operator const std::map<std::string, PValue> &() const
		{
			return (this->m_map);
		}
		operator std::map<std::string, PValue> &()
		{
			return (this->m_map);
		}
	public:
		bool is_empty(void) const;
		bool contains(const std::string &key) const;
		bool has_field(const std::string &key) const;
		Value *at(const std::string &key) const;
		void remove(const std::string &key);
		std::set<std::string> keys(void) const;
		void set_bool(const std::string &key, bool b);
		void set_int(const std::string &key, int b);
		void set_double(const std::string &key, double b);
		void set_string(const std::string &key, std::string b);
		void set_value(const std::string &key, const Value &v);
		Array *set_array(const std::string &key);
		Object *set_object(const std::string &key);
		//
		bool get_bool(const std::string &key) const;
		int get_int(const std::string &key) const;
		double get_double(const std::string &key) const;
		std::string get_string(const std::string &key) const;
		Array *get_array(const std::string &key) const;
		Object *get_object(const std::string &key) const;
		//
		std::ostream & write_to(std::ostream &os) const;
		std::string to_string(void) const;
	protected:
		void set(const std::string &key, PValue v);
		void set_array(const std::string &key, PArray b);
		void set_object(const std::string &key, PObject b);
	private:
		std::map<std::string, PValue> m_map;
	}; // class Object
	   /////////////////////////////////////
}// namespace geninfo
 /////////////////////////////
#endif // __VALUE_H__
