#pragma once
#ifndef __PERSON_H__
#define  __PERSON_H__
/////////////////////////////////
#include "baseitem.h"
//////////////////////////////
namespace info {
	////////////////////////////
	class PersonRole {
	public:
		PersonRole();
		PersonRole(const std::string &depid, const std::string &role);
		PersonRole(const PersonRole &other);
		PersonRole & operator=(const PersonRole &other);
		~PersonRole();
	public:
		bool operator<(const PersonRole &other) const;
		bool operator==(const PersonRole &other) const;
		const std::string & departementid(void) const;
		void departementid(const std::string &s);
		const std::string & role(void) const;
		void role(const std::string &s);
	private:
		std::string m_depid;
		std::string m_role;
	}; // class PersonRole;
	//////////////////////////
	class Person : public BaseItem
	{
	public:
		static std::shared_ptr<Person> find_by_username(const std::string &suser, IDataManager &oMan);
		static std::vector<std::shared_ptr<Person>> get_all_persons(IDataManager &oMan, int skip = 0, int count = 10);
	public:
		Person();
		Person(const Value &oMap);
		Person(const Person &other);
		Person & operator=(const Person &other);
		virtual ~Person();
	public:
		std::string username(void) const;
		void username(const std::string &s);
		std::string password(void) const;
		void password(const std::string &s);
		std::string firstname(void) const;
		void firstname(const std::string &s);
		std::string lastname(void) const;
		void lastname(const std::string &s);
		std::string email(void) const;
		void email(const std::string &s);
		std::string phone(void) const;
		void phone(const std::string &s);
	public:
		std::vector<PersonRole> roles(void) const;
		bool add_role(const std::string &depid, const std::string &role);
		//
		std::set<std::string> departementids(void) const;
		void add_anneeid(const std::string &s);
		std::set<std::string> anneeids(void) const;
		std::set<std::string> semestreids(void) const;
		void add_semestreid(const std::string &s);
		std::set<std::string> groupeids(void) const;
		void add_groupeid(const std::string &s);
		std::set<std::string> uniteids(void) const;
		void add_uniteid(const std::string &s);
		std::set<std::string> matiereids(void) const;
		void add_matiereid(const std::string &s);
		std::set<std::string> affectationids(void) const;
		void add_affectationid(const std::string &s);
		std::set<std::string> eventids(void) const;
		void add_eventid(const std::string &s);
	public:
		std::string fullname(void) const;
		bool check_password(const std::string &cpass) const;
		void change_password(const std::string &s);
		void reset_password(void);
	public:
		std::string dossier(void) const;
		void dossier(const std::string &s);
		std::string sexe(void) const;
		void sexe(const std::string &s);
		std::string birth_date(void) const;
		void birth_date(const std::string &s);
		std::string ville(void) const;
		void ville(const std::string &s);
		std::string etablissement(void) const;
		void etablissement(const std::string &s);
		std::string serie_bac(void) const;
		void serie_bac(const std::string &s);
		std::string option_bac(void) const;
		void option_bac(const std::string &s);
		std::string mention_bac(void) const;
		void mention_bac(const std::string &s);
		std::string etudes_superieures(void) const;
		void etudes_superieures(const std::string &s);
		std::string apb(void) const;
		void apb(const std::string &s);
		std::string redoublant(void) const;
		void redoublant(const std::string &s);
	public:
		virtual std::string store_prefix(void) const;
		virtual std::string create_id(void) const;
		virtual bool is_storeable(void) const;
		virtual std::string text(void) const;
	};
}// namespace geninfo
///////////////////////////////////
#endif //  __PERSON_H__
