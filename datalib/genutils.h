#pragma once
#ifndef __GENUTILS_H__
#define __GENUTILS_H__
/////////////////////////////////
#include <cpprest/json.h>
/////////////////////////////////
#include <memory>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <iterator>
#include <iomanip>
///////////////////////////////
namespace info {
	//////////////////////////////
	extern utility::string_t trim(const utility::string_t &s);
	extern utility::string_t to_upper(const utility::string_t &s);
	extern utility::string_t to_lower(const utility::string_t &s);
	////////////////////////////
	extern std::string convert_to_string(const utility::string_t &s);
	extern utility::string_t convert_from_string(const std::string &s);
	extern utility::string_t url_encode(const utility::string_t &url);
	///////////////////////////////
	extern std::set<utility::string_t> value_to_string_set(const 
web::json::value &v);
	extern web::json::value string_set_to_value(const 
std::set<utility::string_t> &oSet);
}// geninfo
 /////////////////////////////////
#endif // __GENUTILS_H__
