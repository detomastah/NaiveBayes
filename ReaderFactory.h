/*
 * ReaderFactory.h
 *
 *  Created on: 06-01-2012
 *      Author: qcor
 */

#include <string>
#include <map>
#ifndef READERFACTORY_H_
#define READERFACTORY_H_
class Reader;
class ReaderFactory {
public:
	ReaderFactory();
	virtual ~ReaderFactory();
	bool registerReader(std::string id, Reader* newReader);
	Reader* create(std::string id);

private:
	std::map<std::string,Reader*> readerMap;

};

#endif /* READERFACTORY_H_ */
