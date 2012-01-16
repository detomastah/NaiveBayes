/*
 * Testy_jednostkowe.cpp
 *
 *  Created on: 14-01-2012
 *      Author: qcor
 */

#include "Data.h"
#include <fstream>
#include "ReaderFactory.h"
#include "ReaderCSV.h"
#include <boost/test/unit_test.hpp>
#include <boost/test/included/unit_test_framework.hpp>
#include <boost/test/test_tools.hpp>

using namespace std;
typedef std::pair <std::list<float>, std::string > dataPair;
#define BOOST_TEST_MODULE TestReadingAndDataHoldingKlasyfikatorBayesa
using boost::unit_test::test_suite;

BOOST_AUTO_TEST_CASE( testingReaderFactory )
{
	ReaderFactory testReaderFactory;
	testReaderFactory.registerReader("CSV",new ReaderCSV());
	Reader* myReader=testReaderFactory.create("CSV");
	ReaderCSV* testCSVPointer = dynamic_cast<ReaderCSV*>(myReader);
	BOOST_CHECK(testCSVPointer);
	BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE( testingDataCreation )
{
	ReaderFactory f;
	f.registerReader("CSV",new ReaderCSV());
	Reader* myReader=f.create("CSV");
	
	Data* d;
	ifstream myfile ("example.txt");
	d = myReader->read(myfile);
	
	Data::iterator testRowIterator = d->begin();
	
	if(testRowIterator == d->end())
	{
		BOOST_ERROR("ERROR: EMPTY DATA SET!");
	}
	
	DataRow row = *testRowIterator;
	
	BOOST_CHECK(row.getValues()[0] == 1.1f);
	BOOST_CHECK(row.getValues()[0] == 1.7f);
}

test_suite* init_unit_test_suite( int, char* [] ) {
	test_suite* test= BOOST_TEST_SUITE( "testingReaderFactory" );

	return test;
}

