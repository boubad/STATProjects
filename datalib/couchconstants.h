#pragma once
#ifndef __COUCHCONSTANTS_H__
#define __COUCHCONSTANTS_H__
////////////////////////////////
#include <cpprest/json.h>
/////////////////////////////
namespace info {
	class CouchConstants
	{
	public:
		static const utility::string_t BASEURL;
		static const utility::string_t DATABASE;
		//
		static const utility::string_t QUESTION_STRING;
		static const utility::string_t AND_STRING;
		static const utility::string_t QUOTE_STRING;
		//
		static const utility::string_t COMMITTED_UPDATE_SEQ;
		static const utility::string_t COMPACT_RUNNING;
		static const utility::string_t DB_NAME;
		static const utility::string_t DISK_FORMAT_VERSION;
		static const utility::string_t DATA_SIZE;
		static const utility::string_t DISK_SIZE;
		static const utility::string_t DOC_COUNT;
		static const utility::string_t DOC_DEL_COUNT;
		static const utility::string_t INSTANCE_START_TIME;
		static const utility::string_t PURGE_SEQ;
		static const utility::string_t UPDATE_SEQ;
		//
		static const utility::string_t WELCOME;
		static const utility::string_t VENDOR;
		static const utility::string_t COUCHDB;
		static const utility::string_t UUID;
		static const utility::string_t VERSION;
		static const utility::string_t NAME;
		//
		static const utility::string_t LOCATION;
		static const utility::string_t REASON;
		static const utility::string_t ERROR;
		static const utility::string_t REV;
		static const utility::string_t ID;
		static const utility::string_t OK;
		//
		static const utility::string_t OFFSET;
		static const utility::string_t TOTAL_ROWS;
		static const utility::string_t ROWS;
	};
}// namespace geninfo
#endif // __COUCHCONSTANTS_H__
