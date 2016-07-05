#pragma once
#ifndef __UNITE_H__
#define  __UNITE_H__
////////////////////////////////
#include "depsiglenameitem.h"
//////////////////////////////
namespace info {
	class Matiere;
	/////////////////////////////
	class Unite : public DepSigleNamedItem
	{
	public:
		Unite();
		Unite(const Value &oMap);
		Unite(const Departement &oDep);
		Unite(const Unite &other);
		Unite & operator=(const Unite &other);
		virtual ~Unite();
	public:
		int order(void) const;
		void order(int n);
	public:
		virtual std::string store_prefix(void) const;
	public:
		std::vector<std::shared_ptr<Matiere>> matieres(IDataManager &oMan);
	};
}// namespace gebinfo
#endif //  __UNITE_H__
