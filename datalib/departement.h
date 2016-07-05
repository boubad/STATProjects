#pragma once
#ifndef __DEPARTEMENT_H__
#define  __DEPARTEMENT_H__
//////////////////////////////////
#include "siglenameitem.h"
/////////////////////////////////
namespace info {
	class Departement;
	class Groupe;
	class Unite;
	class Annee;
	class Etudiant;
	class Enseignant;
	class Administrator;
	//////////////////////////
	typedef std::shared_ptr<Departement> PDepartement;
	////////////////////////////////
	class Departement : public SigleNamedItem
	{
	public:
		static std::vector<PDepartement> get_all_departements(IDataManager &oMan, int skip = 0, int count = 10);
	public:
		Departement();
		Departement(const Value &oMap);
		Departement(const Departement &other);
		Departement & operator=(const Departement & other);
		~Departement();
	public:
		virtual std::string store_prefix(void) const;
	public:
		std::vector<std::shared_ptr<Groupe>> groupes(IDataManager &oMan);
		std::vector<std::shared_ptr<Unite>> unites(IDataManager &oMan);
		std::vector<std::shared_ptr<Annee>> annees(IDataManager &oMan);
		std::vector<std::shared_ptr<Enseignant>> enseignants(IDataManager &oMan, int skip = 0, int count = 10);
		std::vector<std::shared_ptr<Etudiant>> etudiants(IDataManager &oMan, int skip = 0, int count = 10);
		std::vector<std::shared_ptr<Administrator>> administrators(IDataManager &oMan, int skip = 0, int count = 10);
	};
}// namespace geninfo
///////////////////////////
#endif // __DEPARTEMENT_H__
