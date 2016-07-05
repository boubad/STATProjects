#pragma once
#ifndef __ANNEE_H__
#define __ANNEE_H__
/////////////////////////
#include "depsiglenameitem.h"
////////////////////////////////
namespace info {
	class Semestre;
	/////////////////////////////
	class Annee : public DepSigleNamedItem
	{
	public:
		Annee();
		Annee(const Value &oMap);
		Annee(const Departement &dep);
		Annee(const Annee &other);
		Annee & operator=(const Annee &other);
		virtual ~Annee();
	public:
		std::string start_date(void) const;
		void start_date(const std::string &s);
		std::string end_date(void) const;
		void end_date(const std::string &s);
		std::vector<std::shared_ptr<Semestre>> semestres(IDataManager &oMan);
	public:
		virtual std::string store_prefix(void) const;
		virtual std::string create_id(void) const;
		virtual bool is_storeable(void) const;
	};
	////////////////////////////////
}// namespace geninfo
#endif // __ANNEE_H__
