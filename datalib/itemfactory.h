#pragma once
#ifndef __ITEMFACTORY_H__
#define __ITEMFACTORY_H__
/////////////////////////////////////
#include <memory>
///////////////////////////////////
namespace info {
	class BaseItem;
	class Value;
	//////////////////////////
	class ItemFactory
	{
	public:
		ItemFactory();
		ItemFactory(const ItemFactory &other);
		ItemFactory & operator=(const ItemFactory &other);
		virtual ~ItemFactory();
	public:
		std::shared_ptr<BaseItem> create(const Value &oMap, bool *pOk = nullptr) const;
	};
}// namespace geninfo
///////////////////////////////////
#endif // __ITEMFACTORY_H__
