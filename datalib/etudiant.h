#pragma once
#ifndef __ETUDIANT_H__
#define __ETUDIANT_H__
/////////////////////////////
#include "departementperson.h"
////////////////////////
namespace info {
	class Etudiant : public DepartementPerson
	{
	public:
		Etudiant();
		Etudiant(const Departement &oDep, const Person &oPers);
		Etudiant(const Value &oMap);
		Etudiant(const Etudiant &other);
		Etudiant & operator=(const Etudiant &other);
		virtual ~Etudiant();
	public:
		virtual std::string store_prefix(void) const;
	protected:
		virtual bool check_person(Person &oPers);
	};
}// namespace geninfo
///////////////////////////////
#endif // __ETUDIANT_H__
