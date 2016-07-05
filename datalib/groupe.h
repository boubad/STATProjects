#pragma once
#ifndef __GROUPE_H__
#define __GROUPE_H__
////////////////////////////
#include "depsiglenameitem.h"
///////////////////////////////////////
namespace info {
	class Groupe;
	typedef std::shared_ptr<Groupe> PGroupe;
	///////////////////////////////////////////
	class Groupe : public DepSigleNamedItem
	{
	public:
		static const std::string GENRE_PROMO;
		static const std::string GENRE_TD;
		static const std::string GENRE_TP;
	public:
		Groupe();
		Groupe(const Value &oMap);
		Groupe(const Departement &oDep);
		Groupe(const Groupe &other);
		Groupe & operator=(const Groupe &other);
		virtual ~Groupe();
	public:
		std::string genre(void) const;
		void genre(const std::string &s);
		std::vector<std::string> children_ids(void) const;
		bool add_child(const Groupe &g);
		bool remove_child(const Groupe &g);
		std::vector<PGroupe> children(IDataManager &oMan);
	public:
		virtual std::string store_prefix(void) const;
		virtual bool is_storeable(void) const;
	protected:
		void children_ids(const std::vector<std::string> &ids);
	};
}// namespace geninfo
#endif // #ifndef __GROUPE_H__
