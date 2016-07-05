#pragma once
#ifndef __DOMAINCONSTANTS_H__
#define __DOMAINCONSTANTS_H__
///////////////////////////////
#include <string>
////////////////////////////////
namespace info
{
	class DomainConstants
	{
	public:
		static const std::string TYPE;
		static const std::string ID;
		static const std::string REV;
		static const std::string STATUS;
		static const std::string DESCRIPTION;
		static const std::string DELETED;
		static const std::string SIGLE;
		static const std::string NAME;
		static const std::string ORDER;
		static const std::string GENRE;
		static const std::string CHILDRENIDS;
		static const std::string STARTDATE;
		static const std::string ENDDATE;
		static const std::string MODULE;
		static const std::string COEFFICIENT;
		static const std::string ECS;
		static const std::string DEPARTEMENTID;
		static const std::string UNITEID;
		static const std::string ANNEEID;
		static const std::string MATIEREID;
		static const std::string SEMESTREID;
		static const std::string GROUPEID;
		static const std::string ENSEIGNANTID;
		static const std::string ETUDIANTID;
		static const std::string ENSEIGNANTAFFECTATIONID;
		static const std::string ETUDIANTAFFECTATIONID;
		static const std::string GROUPEEVENTID;
		static const std::string LOCATION;
		static const std::string STARTTIME;
		static const std::string ENDTIME;
		static const std::string MINNOTE;
		static const std::string MAXNOTE;
		static const std::string NOTE;
		static const std::string USERNAME;
		static const std::string PASSWORD;
		static const std::string FIRSTNAME;
		static const std::string LASTNAME;
		static const std::string EMAIL;
		static const std::string PHONE;
		static const std::string DOSSIER;
		static const std::string SEXE;
		static const std::string BIRTHDATE;
		static const std::string VILLE;
		static const std::string ETABLISSEMENT;
		static const std::string SERIEBAC;
		static const std::string OPTIONBAC;
		static const std::string MENTIONBAC;
		static const std::string ETUDESSUPERIEURES;
		static const std::string APB;
		static const std::string REDOUBLANT;
		static const std::string DEPARTEMENTSIDS;
		static const std::string UNITESIDS;
		static const std::string ANNEESIDS;
		static const std::string SEMESTRESIDS;
		static const std::string MATIERESIDS;
		static const std::string AFFECTATIONSIDS;
		static const std::string EVENTSIDS;
		static const std::string ADMINISTRATORSIDS;
		static const std::string ENSEIGNANTSIDS;
		static const std::string ETUDIANTSIDS;
		static const std::string GROUPESIDS;
		static const std::string GENRE_PROMO;
		static const std::string GENRE_TD;
		static const std::string GENRE_TP;
		static const std::string GENRE_PRATIQUE;
		static const std::string GENRE_THEORIE;
		static const std::string GENRE_ABSENCE;
		static const std::string GENRE_RETARD;
		static const std::string GENRE_MISC;
		static const std::string GENRE_NOTE;
		static const std::string DEPARTEMENT_TYPE;
		static const std::string GROUPE_TYPE;
		static const std::string UNITE_TYPE;
		static const std::string MATIERE_TYPE;
		static const std::string ANNEE_TYPE;
		static const std::string SEMESTRE_TYPE;
		static const std::string PERSON_TYPE;
		static const std::string ADMINISTRATORPERSON_TYPE;
		static const std::string ENSEIGNANTPERSON_TYPE;
		static const std::string ETUDIANTPERSON_TYPE;
		static const std::string ENSEIGNANTAFFECTATION_TYPE;
		static const std::string ETUDIANTAFFECTATION_TYPE;
		static const std::string GROUPEEVENT_TYPE;
		static const std::string ETUDIANTEVENT_TYPE;
		static const std::string ETUDIANT_TYPE;
		static const std::string ENSEIGNANT_TYPE;
		static const std::string ADMINISTRATOR_TYPE;
		static const std::string SUPERPERSON_TYPE;
		static const std::string ETUDIANTEVENT_PREFIX;
		static const std::string GROUPEEVENT_PREFIX;
		static const std::string ETUDIANTAFFECTATION_PREFIX;
		static const std::string ENSEIGNANTAFFECTATION_PREFIX;
		static const std::string PERSON_PREFIX;
		static const std::string SEMESTRE_PREFIX;
		static const std::string MATIERE_PREFIX;
		static const std::string UNITE_PREFIX;
		static const std::string GROUPE_PREFIX;
		static const std::string ANNEE_PREFIX;
		static const std::string DEPARTEMENT_PREFIX;
		static const std::string ETUDIANT_PREFIX;
		static const std::string ENSEIGNANT_PREFIX;
		static const std::string ADMINISTRATOR_PREFIX;
		static const std::string PERSONID;
		//
		static const std::string ROLES;
		static const std::string ROLE_SUPER;
		static const std::string ROLE_ADMIN;
		static const std::string ROLE_PROF;
		static const std::string ROLE_ETUD;
		static const std::string ROLE_GUEST;
		static const std::string SUPER_USERNAME;
	};
}// namespace geninfo
#endif // __DOMAINCONSTANTS_H__
