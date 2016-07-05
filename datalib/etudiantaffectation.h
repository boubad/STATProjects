#pragma once
#ifndef __ETUDIANTAFFECTATION_H__
#define __ETUDIANTAFFECTATION_H__
//////////////////////////
#include "affectation.h"
/////////////////////////////
namespace info {
	class Etudiant;
	////////////////////////////
	class EtudiantAffectation: public Affectation
	{
	public:
		static std::vector<std::shared_ptr<EtudiantAffectation> >
			get_all_affectations(IDataManager &oMan,
				const std::string &semid = std::string(),
				const std::string &groupeid = std::string(),
				int skip = 0, int limit = 0);
	public:
		EtudiantAffectation();
		EtudiantAffectation(const Etudiant &oEtud, const Semestre &oSem, const Groupe &oGroupe);
		EtudiantAffectation(const Value &oMap);
		EtudiantAffectation(const EtudiantAffectation &other);
		EtudiantAffectation & operator=(const EtudiantAffectation &other);
		virtual ~EtudiantAffectation();
	public:
		std::string etudiantid(void) const;
		void etudiantid(const std::string &s);
		void etudiant(const Etudiant &oEtud);
		std::shared_ptr<Etudiant> get_etudiant(IDataManager &oMan);
	public:
		virtual std::string store_prefix(void) const;
		virtual std::string start_key(void) const;
		virtual std::string create_id(void) const;
		virtual bool is_storeable(void) const;
	};
	//////////////////////////////////////
}// namespace geninfo
////////////////////
#endif //__ETUDIANTAFFECTATION_H__
