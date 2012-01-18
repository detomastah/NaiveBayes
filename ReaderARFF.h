
/*
 * ReaderCSV.h
 *
 *  Created on: 06-01-2012
 *      Author: qcor
 */

#ifndef READERARFF_H_
#define READERARFF_H_

#include "Reader.h"

class ReaderARFF: public Reader {
public:
	ReaderARFF();
	virtual ~ReaderARFF();
	virtual Reader* clone();
	virtual Data* read(std::istream& dataSource);
};

#endif /* READERARFF_H_ */
