#pragma once
#ifndef __SIGLENAMEDITEM_H__
#define __SIGLENAMEDITEM_H__
///////////////////////////////
#include "baseitem.h"
/////////////////////////////
namespace info {
	class SigleNamedItem : public BaseItem
	{
	public:
		SigleNamedItem();
		SigleNamedItem(const Value &oMap);
		SigleNamedItem(const SigleNamedItem &other);
		SigleNamedItem & operator=(const SigleNamedItem &other);
		virtual ~SigleNamedItem();
	public:
		std::string sigle(void) const;
		void sigle(const std::string &s);
		std::string name(void) const;
		void name(const std::string &s);
	public:
		virtual std::string create_id(void) const;
		virtual bool is_storeable(void) const;
		virtual std::string text(void) const;
	};
}// namespace geninfo
/////////////////////////////////////
#endif // __SIGLENAMEDITEM_H__
