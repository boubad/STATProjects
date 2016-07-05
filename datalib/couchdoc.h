#pragma once
/////////////////////
#ifndef __COUCHDOC_H__
#define __COUCHDOC_H__
/////////////////////////
#include <cpprest/json.h>
////////////////////////////
namespace info
{
	using string_t = utility::string_t;
	using value = web::json::value;
	using ostream_t = utility::ostream_t;
	/////////////////////////////
	class ReadDocOptions
	{
	public:
		ReadDocOptions();
		ReadDocOptions(const ReadDocOptions &other);
		ReadDocOptions & operator=(const ReadDocOptions &other);
		~ReadDocOptions();
	public:
		string_t to_query_string(void) const;
	public:
		bool attachments;
		bool att_encoding_info;
		bool conflicts;
		bool deleted_conflicts;
		bool local_seq;
		bool meta;
		bool revs;
		bool revs_info;
		string_t rev;
	}; // class ReadDocOptions
	   /////////////////////////////////
	class AllDocsOptions
	{
	public:
		AllDocsOptions();
		AllDocsOptions(const AllDocsOptions &other);
		AllDocsOptions & operator=(const AllDocsOptions &other);
		~AllDocsOptions();
	public:
		string_t to_query_string(void) const;
	public:
		bool conflicts;
		bool descending;
		bool group;
		bool include_docs;
		bool attachments;
		bool att_encoding_info;
		bool inclusive_end;
		bool reduce;
		bool update_seq;
		size_t group_level;
		size_t limit;
		size_t skip;
		string_t endkey;
		string_t end_key;
		string_t endkey_docid;
		string_t end_key_doc_id;
		string_t key;
		string_t stale;
		string_t startkey;
		string_t start_key;
		string_t startkey_docid;
		string_t start_key_doc_id;
	};// class AllDocsOptions
	  /////////////////////////////////////
	class AllDocsResponse
	{
	public:
		AllDocsResponse();
		AllDocsResponse(const value &val);
		AllDocsResponse(const AllDocsResponse &other);
		AllDocsResponse & operator=(const AllDocsResponse &other);
		~AllDocsResponse();
	public:
		size_t offset(void) const;
		size_t total_rows(void) const;
		size_t update_seq(void) const;
		const std::vector<value> & rows(void) const;
	private:
		size_t _offset;
		size_t _total_rows;
		size_t _update_seq;
		std::vector<value> _rows;
	};// class AllDocsResponse
	  //////////////////////////////
	class UpdateResponse
	{
	public:
		UpdateResponse();
		UpdateResponse(bool b, const string_t &sid = string_t(), const 
string_t &srev = string_t(),
			const string_t &err = string_t(), const string_t &reas = 
string_t());
		UpdateResponse(const value &val);
		UpdateResponse(const UpdateResponse &other);
		UpdateResponse & operator=(const UpdateResponse &other);
		~UpdateResponse();
	public:
		bool ok(void) const;
		const string_t & id(void) const;
		const string_t & rev(void) const;
		const string_t & error(void) const;
		const string_t & reason(void) const;
		const string_t & location(void) const;
	public:
		void to_map(value &oMap) const;
		ostream_t & write_to(ostream_t &os) const;
	private:
		bool _ok;
		string_t _id;
		string_t _rev;
		string_t _error;
		string_t _reason;
		string_t _location;
	};// class UpdateResponse
	  /////////////////////////////////
	class VendorInfo {
	public:
		VendorInfo();
		VendorInfo(const value &val);
		VendorInfo(const VendorInfo &other);
		VendorInfo & operator=(const VendorInfo &other);
		~VendorInfo();
	public:
		const string_t & version(void) const;
		const string_t & name(void) const;
		void to_map(value &oMap) const;
	private:
		string_t _version;
		string_t _name;
	};// class VendorInfo;
	class ServerInfo
	{
	public:
		ServerInfo();
		ServerInfo(const value &val);
		ServerInfo(const ServerInfo &other);
		ServerInfo & operator=(const ServerInfo &other);
		~ServerInfo();
	public:
		const string_t & couchdb(void) const;
		const string_t & uuid(void) const;
		const string_t & version(void) const;
		const VendorInfo & vendor(void) const;
		bool is_online(void) const;
		void to_map(value &oMap) const;
		ostream_t & write_to(ostream_t &os) const;
	private:
		string_t _couchdb;
		string_t _uuid;
		string_t _version;
		VendorInfo _vendor;
	};
	////////////////////////////
	class DatabaseInfo {
	public:
		DatabaseInfo();
		DatabaseInfo(const value &oMap);
		DatabaseInfo(const DatabaseInfo &other);
		DatabaseInfo & operator=(const DatabaseInfo &other);
		~DatabaseInfo();
	public:
		ostream_t & write_to(ostream_t &os) const;
		size_t committed_update_seq(void) const;
		bool compact_running(void) const;
		string_t db_name(void) const;
		size_t disk_format_version(void) const;
		size_t data_size(void) const;
		size_t disk_size(void) const;
		size_t doc_count(void) const;
		size_t doc_del_count(void) const;
		string_t instance_start_time(void) const;
		size_t purge_seq(void) const;
		size_t update_seq(void) const;
	private:
		value _m_val;
	}; // class DatabaseInfo
	   //////////////////////////////
}// namespace geninfo
 ////////////////////////////////////
inline info::ostream_t & operator<<(info::ostream_t &os, const 
info::DatabaseInfo &info) {
	return info.write_to(os);
}
inline info::ostream_t & operator<<(info::ostream_t &os, const 
info::ServerInfo &info) {
	return info.write_to(os);
}
inline info::ostream_t & operator<<(info::ostream_t &os, const 
info::UpdateResponse &info) {
	return info.write_to(os);
}
/////////////////////////////
#endif // __COUCHDOC_H__
