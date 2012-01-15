/*
 * Data.cpp
 *
 *  Created on: 06-01-2012
 *      Author: qcor
 */

#include "Data.h"

void DataRow::addValue(float value) 
{
	values.push_back(value); 
}

void DataRow::setLabel(std::string label)
{
	this->label = label;
}

std::string DataRow::getLabel()
{
	return this->label;
}

const std::vector<float>& DataRow::getValues()
{
	return this->values;
}

//------------------------

Data::Data()
{
	//rowsIterator=rows.end();
}

Data::~Data()
{
	// TODO Auto-generated destructor stub
}

void Data::addRow(DataRow row)
{
	rows.push_back(row);
}


