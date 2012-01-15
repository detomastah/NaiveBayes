/*
 * Reader.h
 *
 *  Created on: 06-01-2012
 *      Author: qcor
 */
#include <list>
#include <iostream>
#ifndef READER_H_
#define READER_H_

class Data;
class Reader {
public:
	Reader();
	virtual ~Reader();
	virtual Reader* clone() = 0;
	virtual Data* read(std::istream& dataSource) = 0;
protected:
	void addDataRow(Data* data, std::list<float> floatList, std::string label);
private:


};

#endif /* READER_H_ */
