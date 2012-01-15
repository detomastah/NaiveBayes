/*
 * Driver.cpp
 *
 *  Created on: 06-01-2012
 *      Author: qcor
 */
#include "Data.h"
#include <fstream>
#include "ReaderFactory.h"
#include "ReaderCSV.h"
#include "NaiveBayes.h"

using namespace std;
typedef std::pair <std::list<float>, std::string > dataPair;
int main()
{
	ReaderFactory f;
	f.registerReader("CSV",new ReaderCSV());
	Reader* myReader=f.create("CSV");

	list<float> L1;
	L1.push_back(1);
	L1.push_back(2);
	L1.push_back(3);
	L1.push_back(4);
	list<float> L2;
	L2.push_back(5);
	L2.push_back(6);
	L2.push_back(7);
	L2.push_back(8);
	string s1 = "s1";
	string s2 = "s2";
	cout<< "MOJA LISTA : " << *(L1.begin()) << endl;
	list<float> L3;
	Data* d;
	ifstream myfile ("example.txt");
	d = myReader->read(myfile);
	
	NormalModel nm;
	NaiveBayes nb;
	nm.setTrainSet(d);
	nm.train();
	nb.setModel(&nm);
	nb.eval();

	//d.addRow(L1,s1);
	//d.addRow(L2,s2);

	Data::iterator allDataIter = d->begin();
	for(; allDataIter != d->end() ; allDataIter++)
	{
		DataRow tmpPair = *allDataIter;
		std::vector<float>::const_iterator numberIter = tmpPair.getValues().begin();
		for(; numberIter != tmpPair.getValues().end() ; numberIter++)
		{
			cout << "Jacek is the besciak: " << *numberIter << endl;
		}
		cout  << "a mo¿e nie " << tmpPair.getLabel() << endl << endl;
	}

}








////	/*
//
//	Data::myiterator x= d.begin();
//	Data::myiterator x1= d.begin();
//	dataPair test = *x;
//	cout<<"YOYO MADAFAKA STRING 232 3 " << *(test.first.begin()) << endl;
//	cout<<"YOYO MADAFAKA STRING 123123 21" << test.second << endl;
//	x++;
//	test=*x;
//
//	//cout<<"YOYO MADAFAKA myData  " << d.myData.begin(). << endl;
//
//	cout<<"YOYO MADAFAKA STRING 232 3 " << *(test.first.begin()) << endl;
//	cout<<"YOYO MADAFAKA STRING 123123 21" << test.second << endl;
////	cout<<"YOYO MADAFAKA STRING 232 3 " << *((*x).first.begin()) << endl;
////	cout<<"YOYO MADAFAKA STRING 123123 21" << (*x1).second << endl;
//	L3=(*x).first;
//	int z;
//	cout<<"bleble" << endl;
//	//L3.begin();
//
//	 //cout<<"YOYO MADAFAKA pierwszy numerek " <<*(((*x)->first).begin()) << endl;
//	//list<float>::iterator liczby = ((*x)->first).begin();
//	 return 0;
//	// */
//}
