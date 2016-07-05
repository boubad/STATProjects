#pragma once
#ifndef __PERSONITEM_H__
#define __PERSONITEM_H__
////////////////////////////////////
#include "baseitem.h"
/////////////////////////////
namespace info {
	class Person;
	//////////////////////////////////
	class PersonItem : public BaseItem
	{
	public:
		PersonItem();
		PersonItem(const Value &oMap);
		PersonItem(const Person &oPers);
		PersonItem(const PersonItem &other);
		PersonItem & operator=(const PersonItem &other);
		virtual ~PersonItem();
	public:
		void person(const Person &oPers);
		std::string personid(void) const;
		void personid(const std::string &s);
		std::string firstname(void) const;
		std::string lastname(void) const;
		std::string fullname(void) const;
		std::shared_ptr<Person> get_person(IDataManager &oMan);
	public:
		virtual bool is_storeable(void) const;
		virtual bool save(IDataManager &oMan);
	protected:
		virtual bool check_person(Person &oPers);
	};
}// namespace geninfo
#endif // __PERSONITEM_H__
