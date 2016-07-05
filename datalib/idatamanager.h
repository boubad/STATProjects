#pragma once
#ifndef __IDATAMANAGER_H__
#define __IDATAMANAGER_H__
////////////////////////////////
#include "basedoc.h"
////////////////////////////////////
namespace info {
	//////////////////////////////////
	class IDataManager {
	public:
		//
		virtual std::string base_url(void)  = 0;
		virtual void base_url(const std::string &s) = 0;
		virtual std::string database_name(void) = 0;
		virtual void database_name(const std::string &s) = 0;
		//
		virtual Value read_doc(const std::string &id, bool bAttachments = false, bool bMeta = false) = 0;
		virtual Value insert_doc(const Value &doc) = 0;
		virtual Value update_doc(const Value &doc) = 0;
		virtual Value remove_doc(const Value &doc) = 0;
		virtual Value read_docs_range(const std::string &startkey, const std::string &endkey,
			int skip = 0, int limit = 0, bool bDoc = false) = 0;
		virtual std::vector<std::string> read_docs_ids_range(const std::string &startkey, const std::string &endkey,
			int skip = 0, int limit = 0) = 0;
		virtual Value read_docs_array(const std::vector<std::string> &ids) = 0;
		virtual Value maintains_docs(const std::vector<Value> &docs, bool bDelete = false) = 0;
		//
		virtual Value server_info(void) = 0;
		virtual std::vector<std::string> get_uuids(int count = 1) = 0;
		virtual std::vector<std::string> get_all_dbs(void) = 0;
		virtual Value database_info(const std::string &db) = 0;
		virtual Value create_database(const std::string &db) = 0;
		virtual Value delete_database(const std::string &db) = 0;
		virtual bool exists_database(const std::string &db) = 0;
		virtual std::string exists_doc(const std::string &docid) = 0;
		/////////////////////
		IDataManager(){}
		virtual ~IDataManager(){}
	};// class IDataManager
	  ////////////////////////////////////
}// namespace geninfo
 /////////////////////////////////
#endif // __IDATAMANAGER_H__

