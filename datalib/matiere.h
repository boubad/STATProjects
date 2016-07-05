#pragma once
#ifndef __MATIERE_H__
#define __MATIERE_H__
///////////////////////////////
#include "siglenameitem.h"
/////////////////////////////
namespace info {
	class Unite;
	/////////////////////////////////
	class Matiere : public SigleNamedItem
	{
	public:
		Matiere();
		Matiere(const Value &oMap);
		Matiere(const Unite &oUnite);
		Matiere(const Matiere &other);
		Matiere & operator=(const Matiere &other);
		virtual ~Matiere();
	public:
		std::string uniteid(void) const;
		void uniteid(const std::string &s);
		std::string genre(void) const;
		void genre(const std::string &s);
		std::string module(void) const;
		void module(const std::string &s);
		int order(void) const;
		void order(int n);
		double coefficient(void) const;
		void coefficient(double c);
		double ecs(void) const;
		void ecs(double c);
		std::shared_ptr<Unite> get_unite(IDataManager &oMan) const;
	public:
		virtual std::string store_prefix(void) const;
		virtual std::string start_key(void) const;
		virtual std::string create_id(void) const;
		virtual bool is_storeable(void) const;
	};
}// namespace geninfo
///////////////////////////////
#endif // __MATIERE_H__
