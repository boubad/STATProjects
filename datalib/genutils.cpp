//genutils.cpp
////////////////////////
#include "genutils.h"
//////////////////////////////
#include <boost/function_output_iterator.hpp>
#include <boost/bind.hpp>
#include <boost/algorithm/string.hpp>
///////////////////////////////
namespace info
{
	using namespace utility;
	using namespace web::json;
	/////////////////////////////////
	extern string_t trim(const string_t &s) {
		return boost::trim_copy(s);
	}
	extern string_t to_upper(const string_t &s) {
		return boost::to_upper_copy(s);
	}
	extern string_t to_lower(const string_t &s) {
		return boost::to_lower_copy(s);
	}
	///////////////////////////
	extern std::string convert_to_string(const string_t &s)
	{
#ifdef _UTF16_STRINGS
		return utility::conversions::utf16_to_utf8(s);
#else
		std::string sRet = s;
		return sRet;
#endif
	}
	extern string_t convert_from_string(const std::string &s) {
		auto temp = utility::conversions::latin1_to_utf16(s);
		return utility::conversions::to_string_t(temp);
	}
	///////////////////////////
	namespace
	{
		std::string encimpl(std::string::value_type v)
		{
			if (isalnum(v)) {
				return std::string() + v;
			}
			std::ostringstream enc;
			enc << '%' << std::setw(2) << std::setfill('0') << 
std::hex << std::uppercase << int(static_cast<unsigned char>(v));
			return enc.str();
		}
	}

	static std::string urlencode(const std::string& url)
	{
		// Find the start of the query string
		//const std::string::const_iterator start = 
std::find(url.begin(), url.end(), '?');

		// If there isn't one there's nothing to do!
		//if (start == url.end())
		//	return url;

		// store the modified query string
		std::string qstr;

		std::transform(url.begin(), url.end(),
			// Append the transform result to qstr
			
boost::make_function_output_iterator(boost::bind(static_cast<std::string& 
(std::string::*)(const std::string&)>(&std::string::append), &qstr, _1)),
			encimpl);
		//return std::string(url.begin(), start + 1) + qstr;
		return qstr;
	}
	////////////////////////////////
	extern string_t url_encode(const string_t &url)
	{
		std::string surl = convert_to_string(url);
		std::string sRes = urlencode(surl);
		return utility::conversions::to_string_t(sRes);
	}// url_encode
	 //////////////////////////////
	extern std::set<string_t> value_to_string_set(const value &v) {
		std::set<string_t> vec;
		if ((!v.is_null()) && v.is_array()) {
			const web::json::array &oAr = v.as_array();
			for (auto it = oAr.begin(); it != oAr.end(); ++it) {
				const value &vv = *it;
				if ((!vv.is_null()) && vv.is_string()) {
					string_t s = vv.as_string();
					if (!s.empty()) {
						vec.insert(s);
					}
				}
			}// it
		}// array
		return vec;
	}//value_to_string_set
	extern value string_set_to_value(const std::set<string_t> &oSet) {
		std::vector<value> vec;
		for (auto it = oSet.begin(); it != oSet.end(); ++it) {
			string_t s = *it;
			if (!s.empty()) {
				vec.push_back(value::string(s));
			}// s
		}// it
		return value::array(vec);
	}//string_set_to_value
	 /////////////////////////////
}// namespace geninfo
