#pragma once
#ifndef __COUCHDBDATAMANAGER_H__
#define __COUCHDBDATAMANAGER_H__
/////////////////////////////////
#include <string>
#include "value.h"
////////////////////////////////
#include "idatamanager.h"
////////////////////////////////
namespace info {
	//////////////////////////////
	class CouchDBDataManager : public IDataManager
	{
	public:
		CouchDBDataManager();
		CouchDBDataManager(const std::string &baseUrl, const std::string 
&database);
		CouchDBDataManager(const CouchDBDataManager &other);
		CouchDBDataManager & operator=(const CouchDBDataManager &other);
		 ~CouchDBDataManager();
	public:
		virtual std::string base_url(void);
		virtual void base_url(const std::string &s);
		virtual std::string database_name(void);
		virtual void database_name(const std::string &s);
		virtual Value read_doc(const std::string &id, bool bAttachments = false, bool bMeta = false);
		virtual Value insert_doc(const Value &doc);
		virtual Value update_doc(const Value &doc);
		virtual Value remove_doc(const Value &doc);
		virtual Value read_docs_range(const std::string &startkey, const std::string &endkey,
			int skip = 0, int limit = 0, bool bDoc = false);
		virtual std::vector<std::string> read_docs_ids_range(const std::string &startkey, const std::string &endkey,
			int skip = 0, int limit = 0);
		virtual Value read_docs_array(const std::vector<std::string> &ids);
		virtual Value maintains_docs(const std::vector<Value> &docs, bool bDelete = false);
		//
		virtual Value server_info(void);
		virtual std::vector<std::string> get_uuids(int count = 1);
		virtual std::vector<std::string> get_all_dbs(void);
		virtual Value database_info(const std::string &db);
		virtual Value create_database(const std::string &db);
		virtual Value delete_database(const std::string &db);
		virtual bool exists_database(const std::string &db);
		virtual std::string exists_doc(const std::string &docid);
	private:
		std::string m_baseurl;
		std::string m_database;
	};
	////////////////////////
}// namespace geninfo
/////////////////////////////////////
#endif // __COUCHDBDATAMANAGER_H__
