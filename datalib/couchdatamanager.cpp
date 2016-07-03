#include "couchdatamanager.h"
#include "couchdoc.h"
#include "genutils.h"
#include "value.h"
/////////////////////////////
#include <iostream>
#include <iomanip>
///////////////////////////////
#include <cpprest/http_client.h>
#include <pplx/pplxtasks.h>
//////////////////////////////
namespace info {
	using namespace utility;         
	using namespace web;                        
	using namespace web::http;                  
	using namespace web::json;
	using namespace web::http::client;
	using namespace concurrency::streams;
	using namespace pplx;
	//////////////////////////////////////
	const std::string DEFAULT_BASEURL("http://localhost:5984");
	const std::string DEFAULT_DATABASE("geninfo");
	////////////////////////////////
	const utility::string_t ACCEPT_STRING = U("accept");
	const utility::string_t APPLICATION_JSON_STRING = U("application/json");
	const utility::string_t HEADER_IF_MATCH = U("If-Match");
	const utility::string_t HEADER_ETAG = U("ETag");
	const utility::string_t HEADER_COMMIT = U("X-Couch-Full-Commit");
	const utility::string_t HEADER_CONTENT_TYPE = U("Content-Type");
	const utility::string_t STRING_TRUE = U("true");
	const utility::string_t STRING_FALSE = U("false");
	const utility::string_t STRING_EQ = U("=");
	const utility::string_t HEADER_LOCATION = U("Location");
	const utility::string_t STRING_OK = U("ok");
	const utility::string_t STRING_ID = U("_id");
	const utility::string_t STRING_ID2 = U("id");
	const utility::string_t STRING_REV = U("_rev");
	const utility::string_t STRING_REV2 = U("rev");
	const utility::string_t STRING_ATTACHMENTS = U("_attachments");
	const utility::string_t STRING_SEPAR = U("&");
	const utility::string_t STRING_SLASH = U("/");
	const utility::string_t STRING_QUESTION = U("?");
	const utility::string_t STRING_ALL_DBS = U("_all_dbs");
	const utility::string_t STRING_UUIDS_COUNT = U("_uuids?count=");
	const utility::string_t STRING_UUIDS = U("uuids");
	const utility::string_t STRING_ALL_DOCS = U("_all_docs");
	const utility::string_t STRING_KEYS = U("keys");
	const utility::string_t STRING_DOCS = U("docs");
	const utility::string_t STRING_DOC = U("doc");
	const utility::string_t STRING_BULK_DOCS = U("_bulk_docs");
	const utility::string_t STRING_DELETED = U("_deleted");
	const utility::string_t STRING_DELETED2 = U("deleted");
	const utility::string_t STRING_ROWS = U("rows");
	/////////////////////////////////////////////
	const std::string STRING_ID_NATIVE("_id");
	////////////////////////////////////////////
	static Value value_to_infovalue(const web::json::value &v) {
		Value oRet;
		if (!v.is_null()) {
			if (v.is_array()) {
				Array oAr;
				const web::json::array &aa = v.as_array();
				for (auto it = aa.begin(); it != aa.end(); ++it) 
{
					auto v = *it;
					Value vv = value_to_infovalue(v);
					oAr.append_value(vv);
				}// it
				PArray pp = std::make_shared<Array>(oAr);
				oRet = Value(pp);
			}
			else if (v.is_object()) {
				Object oObj;
				const web::json::object &obj = v.as_object();
				for (auto it = obj.begin(); it != obj.end(); 
++it) {
					utility::string_t s = (*it).first;
					web::json::value vx = (*it).second;
					std::string key = convert_to_string(s);
					Value vv = value_to_infovalue(vx);
					oObj.set_value(key, vv);
				}
				PObject oo = std::make_shared<Object>(oObj);
				oRet = Value(oo);
			}
			else if (v.is_boolean()) {
				oRet = Value(v.as_bool());
			}
			else if (v.is_double()) {
				oRet = Value(v.as_double());
			}
			else if (v.is_integer()) {
				oRet = Value(v.as_integer());
			}
			else if (v.is_string()) {
				utility::string_t s = v.as_string();
				std::string ss = convert_to_string(s);
				oRet = Value(ss);
			}
			else if (v.is_number()) {
				oRet = Value(v.as_double());
			}
		}// not null
		return oRet;
	}//value_to_infovalue
	static web::json::value infovalue_to_value(const Value &v) {
		web::json::value oRet;
		if (!v.is_null()) {
			switch (v.type()) {
			case value_type::boolean_type:
				oRet = web::json::value(v.as_bool());
				break;
			case value_type::double_type:
				oRet = web::json::value(v.as_double());
				break;
			case value_type::integer_type:
				oRet = web::json::value(v.as_integer());
				break;
			case value_type::string_type:
			{
				std::string s = v.as_string();
				utility::string_t sc = convert_from_string(s);
				oRet = web::json::value(sc);
			}
			break;
			case value_type::array_type:
			{
				std::vector<web::json::value> oVec;
				Array *pAr = v.as_array();
				if (pAr != nullptr) {
					size_t n = pAr->size();
					for (size_t i = 0; i < n; ++i) {
						PValue pv = (*pAr)[i];
						Value *v = pv.get();
						if (v != nullptr) {
							web::json::value vz = 
infovalue_to_value(*v);
							if (!vz.is_null()) {
								
oVec.push_back(vz);
							}
						}// v
					}// i
				}// pAr
				oRet = web::json::value::array(oVec);
			}
			break;
			case value_type::object_type:
			{
				web::json::value vt = 
web::json::value::object();
				web::json::object & obj = vt.as_object();
				Object *pObj = v.as_object();
				if (pObj != nullptr) {
					std::set<std::string> keys = 
pObj->keys();
					for (auto it = keys.begin(); it != 
keys.end(); ++it) {
						std::string key = *it;
						Value *p = pObj->at(key);
						if (p != nullptr) {
							web::json::value val = 
infovalue_to_value(*p);
							utility::string_t ss = 
convert_from_string(key);
							obj[ss] = val;
						}
					}// it
				}// pObj
				oRet = vt;
			}
			break;
			default:
				break;
			}// type
		}// not null
		return oRet;
	}//infovalue_to_object
	////////////////////////////////
	static task<utility::string_t> st_exists_doc(const utility::string_t 
&baseUrl, const utility::string_t &db, const utility::string_t &id) {
		utility::string_t uri = db;
		uri = uri + STRING_SLASH + id;
		http_client client(baseUrl);
		http_request request(methods::HEAD);
		request.set_request_uri(uri);
		return client.request(request).then([=](http_response response) 
{
			utility::string_t sRet;
			bool bRet = (response.status_code() == status_codes::OK) 
|| (response.status_code() == status_codes::NotModified);
			if (bRet) {
				auto headers = response.headers();
				if (headers.has(HEADER_ETAG)) {
					utility::string_t sx = 
headers[HEADER_ETAG];
					size_t n = sx.length();
					if (n > 2) {
						sRet = sx.substr(1, n - 2);
					}
				}
			}
			else if (response.status_code() != 
status_codes::NotFound) {
				throw http_exception(response.status_code());
			}
			return task_from_result(sRet);
		});
	}//st_exists_doc
	static task<value>  st_read_doc(const utility::string_t &baseUrl, const 
utility::string_t &db, const utility::string_t &id, const ReadDocOptions 
&options) {
		utility::string_t uri = db;
		uri = uri + STRING_SLASH + id;
		http_client client(baseUrl);
		http_request request(methods::GET);
		utility::string_t sreq = options.to_query_string();
		if (!sreq.empty()) {
			uri = uri + sreq;
		}
		request.headers().add(ACCEPT_STRING, APPLICATION_JSON_STRING);
		utility::string_t rev = options.rev;
		if (!rev.empty()) {
			rev = U("\"") + rev + U("\"");
			request.headers().add(HEADER_IF_MATCH, rev);
		}
		request.set_request_uri(uri);
		return client.request(request).then([=](http_response response) 
{
			auto code = response.status_code();
			if ((code == status_codes::OK) || (code == 
status_codes::NotModified)) {
				return response.extract_json();
			}
			return task_from_result(value());
		}).then([=](task<value> t2) {
			value oRet;
			try {
				oRet = t2.get();
			}
			catch (std::exception &ex) {
				throw ex;
			}
			return task_from_result(oRet);
		});
	}// st_read_doc
	static task<value>  st_create_doc(const utility::string_t &baseUrl, 
const utility::string_t &db, const value &doc) {
		utility::string_t uri = db;
		http_client client(baseUrl);
		http_request request(methods::POST);
		request.headers().add(ACCEPT_STRING, APPLICATION_JSON_STRING);
		request.headers().add(HEADER_COMMIT, STRING_TRUE);
		request.set_request_uri(uri);
		request.set_body(doc);
		return client.request(request).then([=](http_response response) 
{
			return response.extract_json();
		}).then([=](task<value> previousTask) {
			value oRet;
			try {
				oRet = previousTask.get();
			}
			catch (std::exception &ex) {
				throw ex;
			}
			return task_from_result(oRet);
		});
	}// st_create_doc
	static pplx::task<value>  st_maintains_doc(const utility::string_t 
&baseUrl, const utility::string_t &db, const value &doc) {
		if (!doc.is_object()) {
			value r;
			return task_from_result(r);
		}
		utility::string_t id;
		std::set<utility::string_t> oSet;
		value docx(doc);
		utility::string_t UNDERSCORE(U("_"));
		object obj = docx.as_object();
		for (auto it = obj.begin(); it != obj.end(); ++it) {
			utility::string_t key = (*it).first;
			if (key != STRING_ID) {
				if (key.find_first_of(UNDERSCORE) == 0) {
					oSet.insert(key);
				}
			}
		}// it
		for (auto it = oSet.begin(); it != oSet.end(); ++it) {
			obj.erase(*it);
		}
		if (obj.find(STRING_ID) != obj.end()) {
			id = (obj[STRING_ID]).as_string();
		}
		std::vector<std::pair<utility::string_t, value>> vec;
		for (auto it = obj.begin(); it != obj.end(); ++it) {
			vec.push_back(std::make_pair((*it).first, 
(*it).second));
		}
		value vNew = value::object(vec);
		if (id.empty()) {
			return st_create_doc(baseUrl, db, vNew);
		}
		utility::string_t rev = st_exists_doc(baseUrl, db, id).get();
		if (rev.empty()) {
			return st_create_doc(baseUrl, db, vNew);
		}
		ReadDocOptions options;
		options.attachments = true;
		value val = st_read_doc(baseUrl, db, id, options).get();
		if ((!val.is_null()) && val.is_object() && 
val.has_field(STRING_ID)) {
			object oo = val.as_object();
			if (val.has_field(STRING_REV)) {
				rev = (val[STRING_REV]).as_string();
				vNew[STRING_REV] = value(rev);
			}
			if (val.has_field(STRING_ATTACHMENTS)) {
				vNew[STRING_ATTACHMENTS] = 
val.at(STRING_ATTACHMENTS);
			}
		}
		utility::string_t uri = db;
		uri = uri + STRING_SLASH + id;
		http_client client(baseUrl);
		http_request request(methods::PUT);
		request.headers().add(ACCEPT_STRING, APPLICATION_JSON_STRING);
		if (!rev.empty()) {
			uri = uri + U("?rev=") + rev;
			request.headers().add(HEADER_IF_MATCH, rev);
		}
		request.headers().add(HEADER_COMMIT, STRING_TRUE);
		request.set_request_uri(uri);
		request.set_body(vNew);
		return client.request(request).then([=](http_response response) 
{
			return response.extract_json();
		}).then([=](task<value> previousTask) {
			value oRet;
			try {
				oRet = previousTask.get();
			}
			catch (std::exception &ex) {
				throw ex;
			}
			return task_from_result(oRet);
		});
	}// st_maintains_doc
	static pplx::task<value>  st_del_doc(const utility::string_t &baseUrl,
		const utility::string_t &db, const utility::string_t &docid) {
		value oDef;
		if (docid.empty()) {
			return pplx::task_from_result(oDef);
		}
		string_t uri = db;
		uri = uri + STRING_SLASH + docid;
		http_client client(baseUrl);
		http_request request(methods::HEAD);
		request.set_request_uri(uri);
		return client.request(request).then([=](http_response response) 
{
			string_t rev;
			bool bRet = (response.status_code() == status_codes::OK) 
|| (response.status_code() == status_codes::NotModified);
			if (bRet) {
				auto headers = response.headers();
				if (headers.has(HEADER_ETAG)) {
					string_t sx = headers[HEADER_ETAG];
					size_t n = sx.length();
					if (n > 2) {
						rev = sx.substr(1, n - 2);
					}
				}
			}
			else {
				throw http_exception(response.status_code());
			}
			http_client cl(baseUrl);
			http_request req(methods::DEL);
			req.headers().add(ACCEPT_STRING, 
APPLICATION_JSON_STRING);
			req.headers().add(HEADER_IF_MATCH, rev);
			req.headers().add(HEADER_COMMIT, STRING_TRUE);
			req.set_request_uri(uri);
			return cl.request(req);
		}).then([=](http_response response) {
			return response.extract_json();
		}).then([=](task<value> previousTask) {
			value oRet;
			try {
				oRet = previousTask.get();
			}
			catch (std::exception &ex) {
				throw ex;
			}
			return task_from_result(oRet);
		});
	}// st_del_doc
	static task<std::vector<string_t> >  st_docs_ids(const string_t 
&baseUrl, const string_t &db, const AllDocsOptions &options) {
		string_t uri = db;
		uri = uri + STRING_SLASH + STRING_ALL_DOCS;
		http_client client(baseUrl);
		http_request request(methods::GET);
		request.headers().add(ACCEPT_STRING, APPLICATION_JSON_STRING);
		string_t sreq = options.to_query_string();
		if (!sreq.empty()) {
			uri = uri + sreq;
		}
		request.set_request_uri(uri);
		return client.request(request).then([=](http_response response) 
{
			if (response.status_code() == status_codes::OK) {
				return response.extract_json();
			}
			else {
				throw http_exception(response.status_code());
			}
		}).then([=](task<value> previousTask) {
			std::vector<string_t> oRet;
			try {
				const value  & jsonvalue = previousTask.get();
				AllDocsResponse rsp = 
AllDocsResponse(jsonvalue);
				auto vv = rsp.rows();
				for (auto it = vv.begin(); it != vv.end(); ++it) 
{
					const value &vx = *it;
					if ((!vx.is_null()) && vx.is_object() && 
vx.has_field(STRING_ID2)) {
						if 
(!vx.has_field(STRING_DELETED2)) {
							string_t s = 
(vx.at(STRING_ID2)).as_string();
							if (!s.empty()) {
								
oRet.push_back(s);
							}
						}
					}
				}// it
			}
			catch (std::exception &ex) {
				throw ex;
			}
			return task_from_result(oRet);
		});
	}//st_docs_ids
	static task<value>  st_get_all_docs(const string_t &baseUrl, const 
string_t &db, const AllDocsOptions &options) {
		string_t uri = db;
		uri = uri + STRING_SLASH + STRING_ALL_DOCS;
		http_client client(baseUrl);
		http_request request(methods::GET);
		request.headers().add(ACCEPT_STRING, APPLICATION_JSON_STRING);
		AllDocsOptions opts(options);
		opts.include_docs = true;
		string_t sreq = opts.to_query_string();
		if (!sreq.empty()) {
			uri = uri + sreq;
		}
		request.set_request_uri(uri);
		return client.request(request).then([=](http_response response) 
{
			if (response.status_code() == status_codes::OK) {
				return response.extract_json();
			}
			else {
				throw http_exception(response.status_code());
			}
		}).then([=](task<value> previousTask) {
			value oRet;
			try {
				std::vector<value> ovec;
				value vr = previousTask.get();
				if ((!vr.is_null()) && vr.is_object() && 
vr.has_field(STRING_ROWS)) {
					const value &va = vr[STRING_ROWS];
					if (va.is_array()) {
						array oar = va.as_array();
						for (auto it = oar.begin(); it 
!= oar.end(); ++it) {
							value vz = *it;
							if (vz.is_object() && 
(!vz.has_field(STRING_DELETED2)) && vz.has_field(STRING_DOC)) {
								value  vo = 
vz[STRING_DOC];
								if 
((!vo.is_null()) && vo.is_object()) {
									
ovec.push_back(vo);
								}
							}
						}// it
					}
				}// vr
				oRet = value::array(ovec);
			}
			catch (std::exception &ex) {
				throw ex;
			}
			return task_from_result(oRet);
		});
	}//get_all_docs
	static task<value> st_bulk_docs(const string_t &baseUrl,
		const string_t &db, const std::vector<value> &oVal) {
		string_t uri = db;
		uri = uri + STRING_SLASH + STRING_BULK_DOCS;
		http_client client(baseUrl);
		http_request request(methods::POST);
		request.headers().add(ACCEPT_STRING, APPLICATION_JSON_STRING);
		request.set_request_uri(uri);
		value oAr = value::array(oVal);
		value doc = value::object();
		doc[STRING_DOCS] = oAr;
		request.set_body(doc);
		return client.request(request).then([=](http_response response) 
{
			if (response.status_code() == status_codes::Created) {
				return response.extract_json();
			}
			throw http_exception(response.status_code());
		}).then([=](task<value> previousTask) {
			value oRet;
			try {
				oRet = previousTask.get();
			}
			catch (std::exception &ex) {
				throw ex;
			}
			return task_from_result(oRet);
		});
	}//:bulk_docs
	static task<value> st_array_docs(const string_t &baseUrl, const string_t 
&db,
		const std::vector<string_t> &keys,
		const AllDocsOptions &options) {
		std::vector<value> vx;
		size_t nx = keys.size();
		for (size_t i = 0; i < nx; ++i) {
			string_t s = keys[i];
			if (!s.empty()) {
				value vw(s);
				vx.push_back(vw);
			}
		}// i
		if (vx.empty()) {
			value ox;
			return task_from_result(ox);
		}
		value oAr = value::array(vx);
		value doc = value::object();
		doc[STRING_KEYS] = oAr;
		string_t uri = db;
		uri = uri + STRING_SLASH + STRING_ALL_DOCS;
		http_client client(baseUrl);
		http_request request(methods::POST);
		request.headers().add(ACCEPT_STRING, APPLICATION_JSON_STRING);
		string_t sreq = options.to_query_string();
		if (!sreq.empty()) {
			uri = uri + sreq;
		}
		request.set_request_uri(uri);
		request.set_body(doc);
		return client.request(request).then([=](http_response response) 
{
			if (response.status_code() == status_codes::OK) {
				return response.extract_json();
			}
			else {
				throw http_exception(response.status_code());
			}
		}).then([=](task<value> previousTask) {
			value oRet;
			try {
				std::vector<value> ovec;
				value vr = previousTask.get();
				if ((!vr.is_null()) && vr.is_object() && 
vr.has_field(STRING_ROWS)) {
					const value &va = vr[STRING_ROWS];
					if (va.is_array()) {
						array oar = va.as_array();
						for (auto it = oar.begin(); it 
!= oar.end(); ++it) {
							value vz = *it;
							if (vz.is_object() && 
(!vz.has_field(STRING_DELETED2)) && vz.has_field(STRING_DOC)) {
								value  vo = 
vz[STRING_DOC];
								if 
((!vo.is_null()) && vo.is_object()) {
									
ovec.push_back(vo);
								}
							}
						}// it
					}
				}// vr
				oRet = value::array(ovec);
			}
			catch (std::exception &ex) {
				throw ex;
			}
			return task_from_result(oRet);
		});
	}//get_array_docs
	static task<std::vector<string_t>> st_get_uuids(const string_t &baseUrl, 
size_t count) {
		http_client client(baseUrl);
		http_request request(methods::GET);
		request.headers().add(ACCEPT_STRING, APPLICATION_JSON_STRING);
		utility::stringstream_t os;
		if (count < 1) {
			count = 1;
		}
		os << STRING_UUIDS_COUNT << count;
		string_t s = os.str();
		request.set_request_uri(s);
		return client.request(request).then([=](http_response response) 
{
			if (response.status_code() == status_codes::OK) {
				return response.extract_json();
			}
			else {
				throw http_exception(response.status_code());
			}
		}).then([=](task<value> previousTask) {
			std::vector<string_t> oRet;
			try {
				const value  & jsonvalue = previousTask.get();
				if ((!jsonvalue.is_null()) && 
jsonvalue.is_object()) {
					if (jsonvalue.has_field(STRING_UUIDS)) {
						auto v = 
(jsonvalue.at(STRING_UUIDS)).as_array();
						size_t n = v.size();
						for (size_t i = 0; i < n; ++i) {
							string_t ss = 
(v.at(i)).as_string();
							oRet.push_back(ss);
						}
					}// uuids
				}// obj
			}
			catch (std::exception &ex) {
				throw ex;
			}
			return task_from_result(oRet);
		});
	}//get_uuids
	static task<std::vector<string_t> > st_get_all_dbs(const string_t 
&baseUrl) {
		http_client client(baseUrl);
		http_request request(methods::GET);
		request.headers().add(ACCEPT_STRING, APPLICATION_JSON_STRING);
		request.set_request_uri(STRING_ALL_DBS);
		return client.request(request).then([=](http_response response) 
{
			if (response.status_code() == status_codes::OK) {
				return response.extract_json();
			}
			else {
				throw http_exception(response.status_code());
			}
		}).then([=](task<value> previousTask) {
			std::vector<string_t> oRet;
			try {
				const value  & jsonvalue = previousTask.get();
				if ((!jsonvalue.is_null()) && 
(jsonvalue.is_array())) {
					size_t n = jsonvalue.size();
					for (size_t i = 0; i < n; ++i) {
						string_t s = 
(jsonvalue.at(i)).as_string();
						oRet.push_back(s);
					}
				}
			}
			catch (std::exception &ex) {
				throw ex;
			}
			return task_from_result(oRet);
		});
	}//get_all_dbs
	static task<value> st_server_info(const string_t &baseUrl) {
		http_client client(baseUrl);
		http_request request(methods::GET);
		request.headers().add(ACCEPT_STRING, APPLICATION_JSON_STRING);
		return client.request(request).then([=](http_response response) 
{
			if (response.status_code() == status_codes::OK) {
				return response.extract_json();
			}
			else {
				throw http_exception(response.status_code());
			}
		}).then([=](task<value> previousTask) {
			value pRet;
			try {
				pRet = previousTask.get();
			}
			catch (std::exception &ex) {
				throw ex;
			}
			return task_from_result(pRet);
		});
	}// get_server_info
	static task<bool> st_exists_database(const string_t &baseUrl, const 
string_t &db) {
		string_t s_uri = db;
		http_client client(baseUrl);
		http_request request(methods::HEAD);
		request.set_request_uri(s_uri);
		return client.request(request).then([=](http_response response) 
{
			bool bRet = (response.status_code() == 
status_codes::OK);
			if ((!bRet) && (response.status_code() != 
status_codes::NotFound)) {
				throw http_exception(response.status_code());
			}
			return task_from_result(bRet);
		});
	}//exists_database
	static task<value> st_database_info(const string_t &baseUrl, const 
string_t &db) {
		string_t s_uri = db;
		http_client client(baseUrl);
		http_request request(methods::GET);
		request.headers().add(ACCEPT_STRING, APPLICATION_JSON_STRING);
		request.set_request_uri(s_uri);
		return client.request(request).then([=](http_response response) 
{
			if (response.status_code() == status_codes::OK) {
				return response.extract_json();
			}
			else {
				throw http_exception(response.status_code());
			}
		}).then([=](task<value> t1) {
			value  oRet;
			try {
				oRet = t1.get();
			}
			catch (std::exception &ex) {
				throw ex;
			}
			return task_from_result(oRet);
		});
	}//get_database_info
	static task<value> st_create_database(const string_t &baseUrl, const 
string_t &db) {
		http_client client(baseUrl);
		http_request request(methods::PUT);
		request.headers().add(ACCEPT_STRING, APPLICATION_JSON_STRING);
		request.set_request_uri(db);
		return client.request(request).then([=](http_response response) 
{
			return response.extract_json();
		}).then([=](task<value> t1) {
			value oRet;
			try {
				oRet = t1.get();
			}
			catch (std::exception &ex) {
				throw ex;
			}
			return task_from_result(oRet);
		});
	}//create_database
	static task<value> st_delete_database(const string_t &baseUrl, const 
string_t &db) {
		http_client client(baseUrl);
		http_request request(methods::DEL);
		request.headers().add(ACCEPT_STRING, APPLICATION_JSON_STRING);
		request.set_request_uri(db);
		return client.request(request).then([=](http_response response) 
{
			return response.extract_json();
		}).then([=](task<value> t1) {
			value oRet;
			try {
				oRet = t1.get();
			}
			catch (std::exception &ex) {
				throw ex;
			}
			return task_from_result(oRet);
		});
	}//delete_database
	 //////////////////////////////
	CouchDBDataManager::CouchDBDataManager() :
		m_baseurl(DEFAULT_BASEURL), m_database(DEFAULT_DATABASE)
	{
	}
	CouchDBDataManager::~CouchDBDataManager()
	{
	}
	CouchDBDataManager::CouchDBDataManager(const std::string &baseUrl,
		const std::string &database) :m_baseurl(baseUrl), 
m_database(database) {
	}
	CouchDBDataManager::CouchDBDataManager(const CouchDBDataManager &other) 
:
		m_baseurl(other.m_baseurl), m_database(other.m_database) {

	}
	CouchDBDataManager & CouchDBDataManager::operator=(const 
CouchDBDataManager &other) {
		if (this != &other) {
			this->m_baseurl = other.m_baseurl;
			this->m_database = other.m_database;
		}
		return (*this);
	}
	/////////////////////////////////
	std::string CouchDBDataManager::base_url(void) {
		return this->m_baseurl;
	}
	void CouchDBDataManager::base_url(const std::string &s) {
		this->m_baseurl = trim(s);
	}
	std::string CouchDBDataManager::database_name(void) {
		return this->m_database;
	}
	void CouchDBDataManager::database_name(const std::string &s) {
		this->m_database = trim(s);
	}
	///////////////////////////////
	Value CouchDBDataManager::read_doc(const std::string &sid, bool 
bAttachments /* = false*/, bool bMeta /*= false*/) {
		Value oRet;
		try {
			string_t url = convert_from_string(this->m_baseurl);
			string_t db = convert_from_string(this->m_database);
			string_t id = convert_from_string(sid);
			ReadDocOptions opts;
			opts.attachments = bAttachments;
			opts.meta = bMeta;
			value v = st_read_doc(url, db, id, opts).get();
			oRet = value_to_infovalue(v);
		}
		catch (...) {}
		return oRet;
	}// read_doc
	Value CouchDBDataManager::insert_doc(const Value &doc) {
		Value oRet;
		try {
			string_t url = convert_from_string(this->m_baseurl);
			string_t db = convert_from_string(this->m_database);
			value v = infovalue_to_value(doc);
			value vr = st_maintains_doc(url, db, v).get();
			oRet = value_to_infovalue(vr);
		}
		catch (...) {}
		return oRet;
	}
	Value CouchDBDataManager::update_doc(const Value &doc) {
		Value oRet;
		try {
			string_t url = convert_from_string(this->m_baseurl);
			string_t db = convert_from_string(this->m_database);
			value v = infovalue_to_value(doc);
			value vr = st_maintains_doc(url, db, v).get();
			oRet = value_to_infovalue(vr);
		}
		catch (...) {}
		return oRet;
	}
	Value CouchDBDataManager::remove_doc(const Value &doc) {
		Value oRet;
		try {
			if (doc.is_object()) {
				Object *pObj = doc.as_object();
				if ((pObj != nullptr) && 
pObj->contains(STRING_ID_NATIVE)) {
					std::string sid = 
pObj->get_string(STRING_ID_NATIVE);
					if (!sid.empty()) {
						string_t id = 
convert_from_string(sid);
						string_t url = 
convert_from_string(this->m_baseurl);
						string_t db = 
convert_from_string(this->m_database);
						value vr = st_del_doc(url, db, 
id).get();
						oRet = value_to_infovalue(vr);
					}// not empty
				}// id
			}// obj
		}
		catch (...) {}
		return oRet;
	}
	Value CouchDBDataManager::read_docs_range(const std::string &startkey, 
const std::string &endkey,
		int skip /*= 0*/, int limit /*= 0*/, bool bDoc /*= false*/) {
		Value oRet;
		try {
			string_t url = convert_from_string(this->m_baseurl);
			string_t db = convert_from_string(this->m_database);
			string_t s1 = convert_from_string(startkey);
			string_t s2 = convert_from_string(endkey);
			AllDocsOptions opts;
			opts.startkey = s1;
			opts.endkey = s2;
			opts.skip = skip;
			opts.limit = limit;
			opts.include_docs = bDoc;
			value vr = st_get_all_docs(url, db, opts).get();
			oRet = value_to_infovalue(vr);
		}
		catch (...) {}
		return oRet;
	}
	std::vector<std::string> CouchDBDataManager::read_docs_ids_range(const 
std::string &startkey, const std::string &endkey,
		int skip /*= 0 */, int limit /*= 0*/) {
		std::vector<std::string> oRet;
		try {
			string_t url = convert_from_string(this->m_baseurl);
			string_t db = convert_from_string(this->m_database);
			string_t s1 = convert_from_string(startkey);
			string_t s2 = convert_from_string(endkey);
			AllDocsOptions opts;
			opts.startkey = s1;
			opts.endkey = s2;
			opts.skip = skip;
			opts.limit = limit;
			std::vector<string_t> vec = st_docs_ids(url, db, 
opts).get();
			for (auto it = vec.begin(); it != vec.end(); ++it) {
				std::string s = convert_to_string(*it);
				oRet.push_back(s);
			}
		} catch(...){}
		return oRet;
	}
	Value CouchDBDataManager::read_docs_array(const std::vector<std::string> 
&ids) {
		Value oRet;
		try {
			std::vector<string_t> oids;
			for (auto it = ids.begin(); it != ids.end(); ++it) {
				string_t s = convert_from_string(*it);
				if (!s.empty()) {
					oids.push_back(s);
				}
			}// it
			if (!oids.empty()) {
				string_t url = 
convert_from_string(this->m_baseurl);
				string_t db = 
convert_from_string(this->m_database);
				AllDocsOptions opts;
				opts.include_docs = true;
				value vr = st_array_docs(url, db, oids, 
opts).get();
				oRet = value_to_infovalue(vr);
			}
		}
		catch (...) {}
		return oRet;
	}
	Value CouchDBDataManager::maintains_docs(const std::vector<Value> &docs, 
bool bDelete /*= false*/) {
		Value oRet;
		try {
			string_t url = convert_from_string(this->m_baseurl);
			string_t db = convert_from_string(this->m_database);
			std::vector<value> odata;
			for (auto it = docs.begin(); it != docs.end(); ++it) {
				value s = infovalue_to_value(*it);
				string_t sid, rev;
				if (s.is_object()) {
					if (s.has_field(STRING_ID)) {
						sid = 
(s[STRING_ID]).as_string();
						rev = st_exists_doc(url, db, 
sid).get();
					}// id
					if (!rev.empty()) {
						s[STRING_REV] = value(rev);
					}
					if (bDelete) {
						if ((!sid.empty()) && 
(!rev.empty())) {
							s[STRING_DELETED] = 
value(true);
							odata.push_back(s);
						}
					}
					else {
						odata.push_back(s);
					}
				}// object
			}// it
			if (!odata.empty()) {
				value vr = st_bulk_docs(url, db, odata).get();
				oRet = value_to_infovalue(vr);
			}
		}
		catch (...) {}
		return oRet;
	}
	///////////////////////////////////
	Value CouchDBDataManager::server_info(void) {
		Value oRet;
		try {
			string_t url = convert_from_string(this->m_baseurl);
			value vr = st_server_info(url).get();
			oRet = value_to_infovalue(vr);
		}
		catch (...) {}
		return oRet;
	}
	std::vector<std::string> CouchDBDataManager::get_uuids(int count/* = 
1*/) {
		std::vector<std::string> oRet;
		try {
			string_t url = convert_from_string(this->m_baseurl);
			std::vector<string_t> vec = st_get_uuids(url, 
count).get();
			for (auto it = vec.begin(); it != vec.end(); ++it) {
				std::string s = convert_to_string(*it);
				oRet.push_back(s);
			}
		}
		catch (...) {}
		return oRet;
	}
	std::vector<std::string> CouchDBDataManager::get_all_dbs(void) {
		std::vector<std::string> oRet;
		try {
			string_t url = convert_from_string(this->m_baseurl);
			std::vector<string_t> vec = st_get_all_dbs(url).get();
			for (auto it = vec.begin(); it != vec.end(); ++it) {
				std::string s = convert_to_string(*it);
				oRet.push_back(s);
			}
		}
		catch (...) {}
		return oRet;
	}
	Value CouchDBDataManager::database_info(const std::string &db) {
		Value oRet;
		try {
			string_t url = convert_from_string(this->m_baseurl);
			string_t sdb = convert_from_string(db);
			value vr = st_database_info(url, sdb).get();
			oRet = value_to_infovalue(vr);
		}
		catch (...) {}
		return oRet;
	}
	Value CouchDBDataManager::create_database(const std::string &db) {
		Value oRet;
		try {
			string_t url = convert_from_string(this->m_baseurl);
			string_t sdb = convert_from_string(db);
			value vr = st_create_database(url, sdb).get();
			oRet = value_to_infovalue(vr);
		}
		catch (...) {}
		return oRet;
	}
	Value CouchDBDataManager::delete_database(const std::string &db) {
		Value oRet;
		try {
			string_t url = convert_from_string(this->m_baseurl);
			string_t sdb = convert_from_string(db);
			value vr = st_delete_database(url, sdb).get();
			oRet = value_to_infovalue(vr);
		}
		catch (...) {}
		return oRet;
	}
	bool CouchDBDataManager::exists_database(const std::string &db) {
		bool oRet = false;
		try {
			string_t url = convert_from_string(this->m_baseurl);
			string_t sdb = convert_from_string(db);
			oRet = st_exists_database(url, sdb).get();
		}
		catch (...) {}
		return oRet;
	}
	std::string CouchDBDataManager::exists_doc(const std::string &docid) {
		std::string oRet;
		try {
			string_t url = convert_from_string(this->m_baseurl);
			string_t db = convert_from_string(this->m_database);
			string_t id = convert_from_string(docid);
			string_t s = st_exists_doc(url, db, id).get();
			oRet = convert_to_string(s);
		}
		catch (...) {}
		return oRet;
	}
	/////////////////////////////////
}// namespace geninfo
