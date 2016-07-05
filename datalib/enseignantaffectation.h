#pragma once
#ifndef __ENSEIGNANTAFFECTATION_H__
#define __ENSEIGNANTAFFECTATION_H__
//////////////////////////
#include "affectation.h"
/////////////////////////////
namespace info {
	class Enseignant;
	class Matiere;
	////////////////////////////
	class EnseignantAffectation : public Affectation
	{
	public:
		static std::vector<std::shared_ptr<EnseignantAffectation> >
			get_all_affectations(IDataManager &oMan,
				const std::string &semid = std::string(),
				const std::string &matid = std::string(),
				const std::string &groupeid = std::string(),
				int skip = 0, int limit = 0);
	public:
		EnseignantAffectation();
		EnseignantAffectation(const Enseignant &oProf, const Semestre &oSem, 
			const Matiere &oMat, const Groupe &oGroupe);
		EnseignantAffectation(const Value &oMap);
		EnseignantAffectation(const EnseignantAffectation &other);
		EnseignantAffectation & operator=(const EnseignantAffectation &other);
		virtual ~EnseignantAffectation();
	public:
		std::string enseignantid(void) const;
		void enseignantid(const std::string &s);
		void enseignant(const Enseignant &oProf);
		std::string matiereid(void) const;
		void matiereid(const std::string &s);
		void matiere(const Matiere &oMat);
		std::shared_ptr<Enseignant> get_enseignant(IDataManager &oMan);
		std::shared_ptr<Matiere> get_matiere(IDataManager &oMan);
	public:
		virtual std::string store_prefix(void) const;
		virtual std::string start_key(void) const;
		virtual std::string create_id(void) const;
		virtual bool is_storeable(void) const;
	};
	//////////////////////////////////////
}// namespace geninfo
 ////////////////////
#endif //__ENSEIGNANTAFFECTATION_H__
