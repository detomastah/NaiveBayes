/*
 * ReaderCSV.cpp
 *
 *  Created on: 06-01-2012
 *      Author: qcor
 */

#include "ReaderARFF.h"
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include "Data.h"

using namespace boost;
ReaderARFF::ReaderARFF() {
	// TODO Auto-generated constructor stub

}

ReaderARFF::~ReaderARFF() {
	// TODO Auto-generated destructor stub
}

Reader* ReaderARFF::clone()
{
	return new ReaderARFF();
}
Data* ReaderARFF::read(std::istream& dataSource)
{
	std::list<float> floatList;
	std::string classification;
	std::string line;
	Data* temp = new Data();

	while (std::getline(dataSource,line) && line != "@DATA")
	{
		//przejscie do sekcji data
	}

	while(std::getline(dataSource,line))
	{
		char_separator<char> sep(", ");
		tokenizer <char_separator<char> > tokens(line, sep);
		tokenizer <char_separator<char> >::iterator tok_iter_2 = tokens.begin();
		++tok_iter_2;
		for (tokenizer<char_separator<char> >::iterator tok_iter = tokens.begin();
				tok_iter != tokens.end(); ++tok_iter,++tok_iter_2)
		{
			if(tok_iter_2 == tokens.end())
			{
				classification = *tok_iter;
				break;
			}
			try
			{
				floatList.push_back(lexical_cast<float> (*tok_iter));
			}
			catch(bad_lexical_cast & e)
			{
				break;
				floatList.clear();
			}
		}
		if(floatList.size() > 0 && classification.compare(""))
		{
			addDataRow(temp,floatList,classification);
			floatList.clear();
		}
		floatList.clear();
		classification = "";
	}
	return temp;
}
