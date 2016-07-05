#pragma once
#ifndef __SEMESTRE_H__
#define __SEMESTRE_H__
/////////////////////////////
#include "siglenameitem.h"
/////////////////////////////////
namespace info {
	class Annee;
	////////////////////////
	class Semestre : public SigleNamedItem
	{
	public:
		Semestre();
		Semestre(const Value &oMap);
		Semestre(const Annee &oAnnee);
		Semestre(const Semestre &other);
		Semestre & operator=(const Semestre &other);
		virtual ~Semestre();
	public:
		std::string anneeid(void) const;
		void anneeid(const std::string &s);
		std::string start_date(void) const;
		void start_date(const std::string &s);
		std::string end_date(void) const;
		void end_date(const std::string &s);
		std::shared_ptr<Annee> get_annee(IDataManager &oMan) const;
	public:
		virtual std::string store_prefix(void) const;
		virtual std::string start_key(void) const;
		virtual std::string create_id(void) const;
		virtual bool is_storeable(void) const;
	};
	/////////////////////////////////
}// namesqpace geninfo
#endif // __SEMESTRE_H__
