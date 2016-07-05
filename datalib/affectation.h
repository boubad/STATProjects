#pragma once
#ifndef __AFFECTATION_H__
#define __AFFECTATION_H__
///////////////////////////////
#include "personitem.h"
/////////////////////////////
namespace info {
	//////////////////////////////
	class DepartementPerson;
	class Semestre;
	class Groupe;
	///////////////////////////
	class Affectation : public PersonItem
	{
	public:
		Affectation();
		Affectation(const DepartementPerson &oPers, const Semestre &oSem, const Groupe &oGroupe);
		Affectation(const Value &oMap);
		Affectation(const Affectation &other);
		Affectation & operator=(const Affectation &other);
		virtual ~Affectation();
	public:
		std::string anneeid(void) const;
		void anneeid(const std::string &s);
		std::string semestreid(void) const;
		void semestreid(const std::string &s);
		std::string groupeid(void) const;
		void groupeid(const std::string &s);
		void semestre(const Semestre &oSem);
		void groupe(const Groupe &oGroupe);
		std::string start_date(void) const;
		void start_date(const std::string &s);
		std::string end_date(void) const;
		void end_date(const std::string &s);
		std::shared_ptr<Groupe> get_groupe(IDataManager &oMan);
		std::shared_ptr<Semestre> get_semestre(IDataManager &oMan);
	public:
		virtual bool is_storeable(void) const;
		virtual std::string start_key(void) const;
	protected:
		virtual bool check_person(Person &oPers);
	};
}// namespace geninfo
#endif // __AFFECTATION_H__
