/*
 * Reader.cpp
 *
 *  Created on: 06-01-2012
 *      Author: qcor
 */

#include "Reader.h"
#include "Data.h"

Reader::Reader() {
	// TODO Auto-generated constructor stub

}

Reader::~Reader() {
	// TODO Auto-generated destructor stub
}

void Reader::addDataRow(Data* data, std::list<float> floatList, std::string label)
{
	DataRow row;
	row.setLabel(label);
	for (std::list<float>::iterator it = floatList.begin(); it != floatList.end(); it++)
		row.addValue(*it);
	data->addRow(row);
	
}
