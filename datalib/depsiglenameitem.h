#pragma once
#ifndef __DEPSIGLENAMEDITEM_H__
#define __DEPSIGLENAMEDITEM_H__
///////////////////////////////
#include "siglenameitem.h"
//////////////////////////////
namespace info {
	class Value;
	class Departement;
	///////////////////////////////
	class DepSigleNamedItem : public SigleNamedItem
	{
	public:
		DepSigleNamedItem();
		DepSigleNamedItem(const Value &oMap);
		DepSigleNamedItem(const Departement &oDep);
		DepSigleNamedItem(const DepSigleNamedItem &other);
		DepSigleNamedItem & operator=(const DepSigleNamedItem &other);
		~DepSigleNamedItem();
	public:
		std::string departementid(void) const;
		void departementid(const std::string &s);
		std::shared_ptr<Departement> get_departement(IDataManager &oMan) const;
	public:
		virtual std::string start_key(void) const;
		virtual bool is_storeable(void) const;
	};
}// namespace geninfo
#endif // __DEPSIGLENAMEDITEM_H__
