#pragma once
#ifndef __ENSEIGNANT_H__
#define __ENSEIGNANT_H__
/////////////////////////////
#include "departementperson.h"
////////////////////////
namespace info {
	class Enseignant : public DepartementPerson
	{
	public:
		Enseignant();
		Enseignant(const Departement &oDep, const Person &oPers);
		Enseignant(const Value &oMap);
		Enseignant(const Enseignant &other);
		Enseignant & operator=(const Enseignant &other);
		virtual ~Enseignant();
	public:
		virtual std::string store_prefix(void) const;
	protected:
		virtual bool check_person(Person &oPers);
	};
}// namespace geninfo
 ///////////////////////////////
#endif // __Enseignant_H__
