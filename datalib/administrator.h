#pragma once
#ifndef __ADMINISTRATOR_H__
#define __ADMINISTRATOR_H__
/////////////////////////////
#include "departementperson.h"
////////////////////////
namespace info {
	class Administrator : public DepartementPerson
	{
	public:
		Administrator();
		Administrator(const Departement &oDep, const Person &oPers);
		Administrator(const Value &oMap);
		Administrator(const Administrator &other);
		Administrator & operator=(const Administrator &other);
		virtual ~Administrator();
	public:
		virtual std::string store_prefix(void) const;
	protected:
		virtual bool check_person(Person &oPers);
	};
}// namespace geninfo
 ///////////////////////////////
#endif // __ADMINISTRATOR_H__
