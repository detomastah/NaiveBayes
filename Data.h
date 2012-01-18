/*
 * Data.h
 *
 *  Created on: 06-01-2012
 *      Author: qcor
 */
#include <list>
#include <vector>
#include <iterator>
#include <utility>
#include <string>
#ifndef DATA_H_
#define DATA_H_

class Reader;
class DataRow;
class Data;

typedef std::list<DataRow>::iterator DataRowIterator;

//pojedynczy wiersz
class DataRow
{
public:
	void addValue(float value);
	const std::vector<float>& getValues();
	void setLabel(std::string label);
	std::string getLabel();
protected:
	std::vector<float> values;
	std::string label;
};

class Data {
public:
	Data();
	void addRow(DataRow row);
	virtual ~Data();
	
	DataRow readNextRow();
	
	class iterator : public std::iterator<std::input_iterator_tag, DataRowIterator >
	{
		DataRowIterator p;
	public:
		iterator(DataRowIterator x) :p(x) {}
		iterator(const iterator& mit) : p(mit.p) {}
		iterator& operator++() {++p;return *this;}
		iterator operator++(int) {iterator tmp(*this); operator++(); return tmp;}
		bool operator==(const iterator& rhs) {return p==rhs.p;}
		bool operator!=(const iterator& rhs) {return p!=rhs.p;}
		DataRow& operator*() {return *p;}
	};
	
	iterator begin()
	{
		return iterator(rows.begin());
	}

	iterator end()
	{
		return iterator(rows.end());
	}

private:
	std::list<DataRow> rows;
};

#endif /* DATA_H_ */
