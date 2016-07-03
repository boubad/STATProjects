#include "couchconstants.h"
////////////////////////////////
namespace info {
	/////////////////////////////
	const utility::string_t 
CouchConstants::BASEURL(U("http://localhost:5984"));
	const utility::string_t CouchConstants::DATABASE(U("geninfo"));
	///////////////////////////////////////////
	const utility::string_t CouchConstants::QUESTION_STRING(U("?"));
	const utility::string_t CouchConstants::AND_STRING(U("&"));
	const utility::string_t CouchConstants::QUOTE_STRING(U("\""));
	//
	const utility::string_t 
CouchConstants::COMMITTED_UPDATE_SEQ(U("committed_update_seq"));
	const utility::string_t 
CouchConstants::COMPACT_RUNNING(U("compact_running"));
	const utility::string_t CouchConstants::DB_NAME(U("db_name"));
	const utility::string_t 
CouchConstants::DISK_FORMAT_VERSION(U("disk_format_version"));
	const utility::string_t CouchConstants::DATA_SIZE(U("data_size"));
	const utility::string_t CouchConstants::DISK_SIZE(U("disk_size"));
	const utility::string_t CouchConstants::DOC_COUNT(U("doc_count"));
	const utility::string_t 
CouchConstants::DOC_DEL_COUNT(U("doc_del_count"));
	const utility::string_t 
CouchConstants::INSTANCE_START_TIME(U("instance_start_time"));
	const utility::string_t CouchConstants::PURGE_SEQ(U("purge_seq"));
	const utility::string_t CouchConstants::UPDATE_SEQ(U("update_seq"));
	////////////////////////////////
	const utility::string_t CouchConstants::WELCOME(U("Welcome"));
	const utility::string_t CouchConstants::VENDOR(U("vendor"));
	const utility::string_t CouchConstants::COUCHDB(U("couchdb"));
	const utility::string_t CouchConstants::UUID(U("uuid"));
	const utility::string_t CouchConstants::VERSION(U("version"));
	const utility::string_t CouchConstants::NAME(U("name"));
	///////////////////////////////////////////
	const utility::string_t  CouchConstants::LOCATION(U("Location"));
	const utility::string_t  CouchConstants::REASON(U("reason"));
	const utility::string_t  CouchConstants::ERROR(U("error"));
	const utility::string_t  CouchConstants::REV(U("rev"));
	const utility::string_t  CouchConstants::ID(U("id"));
	const utility::string_t  CouchConstants::OK(U("ok"));
	/////////////////////////////////////
	const utility::string_t CouchConstants::OFFSET(U("offset"));
	const utility::string_t CouchConstants::TOTAL_ROWS(U("total_rows"));
	const utility::string_t CouchConstants::ROWS(U("rows"));
	/////////////////////////////////////////
}// namespace geninfo
