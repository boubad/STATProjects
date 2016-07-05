#pragma once
#ifndef __ISERVICEFACTORY_H__
#define __ISERVICEFACTORY_H__
////////////////////////////
#include <memory>
#include <string>
////////////////////////////
namespace info {
	///////////////////////////////
	class IDataManager;
	////////////////////////////////
	class IServiceFactory {
	public:
		virtual std::shared_ptr<IDataManager> get_datamanager(const std::string &url, const std::string &database) = 0;
	}; // class IServiceFactory
	////////////////////////////////////
}// namespace geninfo
/////////////////////////////
#endif // __ISERVICEFACTORY_H__
