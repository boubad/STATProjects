#pragma once
#ifndef __BASEEVENT_H__
#define __BASEEVENT_H__
///////////////////////////////
#include "baseitem.h"
/////////////////////////////
namespace info {
	//////////////////////////////
	class DepartementPerson;
	class Semestre;
	class Groupe;
	///////////////////////////
	class BaseEvent : public BaseItem
	{
	public:
		BaseEvent();
		BaseEvent(const Value &oMap);
		BaseEvent(const BaseEvent &other);
		BaseEvent & operator=(const BaseEvent &other);
		virtual ~BaseEvent();
	public:
		std::string genre(void) const;
		void genre(const std::string &s);
		std::string description(void) const;
		void description(const std::string &s);
		std::string event_date(void) const;
		void event_date(const std::string &s);
		std::string event_date(void) const;
	};
}// namespace geninfo
#endif // __AFFECTATION_H__
