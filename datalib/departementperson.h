#pragma once
#ifndef __DEPARTEMENTPERSON_H__
#define __DEPARTEMENTPERSON_H__
////////////////////////////////////
#include "personitem.h"
////////////////////////////
namespace info {
	class Departement;
	/////////////////////////////////////////
	class DepartementPerson : public PersonItem
	{
	public:
		DepartementPerson();
		DepartementPerson(const Departement &oDep, const Person &oPers);
		DepartementPerson(const Value &oMap);
		DepartementPerson(const DepartementPerson &other);
		DepartementPerson & operator=(const DepartementPerson &other);
		virtual ~DepartementPerson();
	public:
		void departement(const Departement &oDep);
		std::string departementid(void) const;
		std::shared_ptr<Departement> get_departement(IDataManager &oMan);
	public:
		virtual std::string start_key(void) const;
		virtual std::string create_id(void) const;
		virtual bool is_storeable(void) const;
		virtual std::string text(void) const;
	};
	/////////////////////////////////////////////
}// namespace geninfo
//////////////////////////////////////
#endif // __DEPARTEMENTPERSON_H__
