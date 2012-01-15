/*
 * ReaderFactory.cpp
 *
 *  Created on: 06-01-2012
 *      Author: qcor
 */

#include "ReaderFactory.h"
#include "Reader.h"
ReaderFactory::ReaderFactory()
{

}

ReaderFactory::~ReaderFactory()
{
	// TODO Auto-generated destructor stub
}

bool ReaderFactory::registerReader(std::string id, Reader* newReader)
{
	if(readerMap.find(id) != readerMap.end())
	{
		return false;
	}
	else
	{
		readerMap[id]=newReader;
		return true;
	}
}

Reader* ReaderFactory::create(std::string id)
{
	if(readerMap.find(id) == readerMap.end())
	{
		return NULL; //tutaj lepie wyrzucać wyjątek niż NULL, ponieważ NULL moze prowadzic do segfaultow
	}
	else
	{
		return readerMap[id]->clone();
	}
}
