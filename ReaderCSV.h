/*
 * ReaderCSV.h
 *
 *  Created on: 06-01-2012
 *      Author: qcor
 */

#ifndef READERCSV_H_
#define READERCSV_H_

#include "Reader.h"

class ReaderCSV: public Reader {
public:
	ReaderCSV();
	virtual ~ReaderCSV();
	virtual Reader* clone();
	virtual Data* read(std::istream& dataSource);
};

#endif /* READERCSV_H_ */
