#pragma once
#ifndef __BASEITEM_H__
#define __BASEITEM_H__
/////////////////////////////
#include "basedoc.h"
/////////////////////////////
namespace info {
	//////////////////////////////
	class IDataManager;
	///////////////////////////////
	class BaseItem : public BaseDoc {
	public:
		static std::string trim(const std::string &s);
		static std::string to_lower(const std::string &s);
		static std::string to_upper(const std::string &s);
		static std::string format_name(const std::string &s);
	public:
		BaseItem();
		BaseItem(const Value &oMap);
		BaseItem(const BaseItem &other);
		BaseItem & operator=(const BaseItem &other);
		virtual ~BaseItem();
	public:
		bool modified(void) const;
		void modified(bool b);
		bool selected(void) const;
		void selected(bool b);
		std::string status(void) const;
		void status(const std::string &s);
		std::string description(void) const;
		void description(const std::string &s);
	public:
		virtual std::string store_prefix(void) const;
		virtual std::string start_key(void) const;
		virtual std::string create_id(void) const;
		virtual bool is_storeable(void) const;
		virtual std::string text(void) const;
		//
		virtual bool load(IDataManager &oMan);
		virtual bool save(IDataManager &oMan);
		virtual bool remove(IDataManager &oMan);
	public:
		virtual void set_bool(const std::string &key, bool b);
		virtual void set_int(const std::string &key, int b);
		virtual void set_double(const std::string &key, double b);
		virtual void set_string(const std::string &key, std::string b);
	public:
		std::string type(void) const;
		std::string end_key(void) const;
		void check_id(void);
	protected:
		void type(const std::string &s);
	private:
		bool m_modified;
		bool m_selected;
	}; // class BaseItem
	///////////////////////////////
}// name
//////////////////////////////
#endif // __BASEITEM_H__
