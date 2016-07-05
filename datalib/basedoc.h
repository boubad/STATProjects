#pragma once
#ifndef __BASEDOC_H__
#define __BASEDOC_H__
/////////////////////////////
#include "value.h"
///////////////////////////////
namespace info
{
	//////////////////////////////////////
	class AttachmentDesc
	{
	public:
		AttachmentDesc();
		AttachmentDesc(const Value &oMap);
		AttachmentDesc(const AttachmentDesc &other);
		AttachmentDesc & operator=(const AttachmentDesc &other);
		~AttachmentDesc();
	public:
		bool stub;
		int revpos;
		int length;
		int encoded_length;
		std::string encoding;
		std::string content_type;
		std::string data;
		std::string digest;
		std::string name;
	};
	//////////////////////////////////
	class RevisionsData
	{
	public:
		RevisionsData();
		RevisionsData(const Value &oMap);
		RevisionsData(const RevisionsData &other);
		RevisionsData & operator=(const RevisionsData &other);
		~RevisionsData();
	public:
		int  start(void) const;
		const std::vector<std::string> & ids(void) const;
	private:
		int _start;
		std::vector<std::string> _ids;
	};// class RevisionsData
	class RevisionInfo
	{
	public:
		RevisionInfo();
		RevisionInfo(const Value &oMap);
		RevisionInfo(const RevisionInfo &other);
		RevisionInfo & operator=(const RevisionInfo &other);
		~RevisionInfo();
	public:
		const std::string & rev(void) const;
		const std::string & status(void) const;
		bool is_available(void) const;
		bool is_deleted(void) const;
	private:
		std::string _rev;
		std::string _status;
	};// class RevisionInfo
	  /////////////////////////////////////
	class BaseDoc
	{
	public:
		BaseDoc();
		BaseDoc(const Value &oMap);
		BaseDoc & operator=(const BaseDoc &other);
		virtual ~BaseDoc();
	public:
		const Value & value(void) const {
			return (this->m_val);
		}
		Value & value(void)  {
			return (this->m_val);
		}
		operator const Value &()const
		{
			return (this->m_val);
		}
		operator Value &()
		{
			return (this->m_val);
		}
	public:
		bool deleted(void) const;
		int local_seq(void) const;
		std::string  id(void) const;
		std::string  rev(void) const;
		std::vector<std::string>  conflicts(void) const;
		std::vector<std::string>  deleted_conflicts(void) const;
		std::vector<RevisionInfo>  revs_info(void) const;
		RevisionsData  revisions(void) const;
		std::map<std::string, AttachmentDesc>  attachments(void) const;
	public:
		bool has_id(void) const;
		bool has_rev(void) const;
		void id(const std::string &s);
		void rev(const std::string &s);
		bool has_field(const std::string &s) const;
		bool is_empty(void) const;
		bool contains(const std::string &key) const;
		Value *at(const std::string &key) const;
		void remove(const std::string &key);
		std::set<std::string> keys(void) const;
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
	public:
		virtual void set_bool(const std::string &key, bool b);
		virtual void set_int(const std::string &key, int b);
		virtual void set_double(const std::string &key, double b);
		virtual void set_string(const std::string &key, std::string b);
	protected:
		Value m_val;
	};
}// geninfo
///////////////////////////////////////////
inline std::ostream & operator<<(std::ostream &os, const info::BaseDoc &doc) {
	return doc.write_to(os);
}
///////////////////////////////////////
#endif // __BASEDOC_H__
