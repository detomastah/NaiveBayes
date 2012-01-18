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
#include "ReaderARFF.h"
#include "NaiveBayes.h"
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
	testReaderFactory.registerReader("ARFF",new ReaderARFF());
	
	Reader* testCSVReader=testReaderFactory.create("CSV");
	ReaderCSV* testCSVPointer = dynamic_cast<ReaderCSV*>(testCSVReader);
	BOOST_CHECK(testCSVPointer);
	
	Reader* testARFFReader=testReaderFactory.create("ARFF");
	ReaderARFF* testARFFPointer = dynamic_cast<ReaderARFF*>(testARFFReader);
	BOOST_CHECK(testARFFPointer);
}

void testData(Data *d) 
{
	Data::iterator testRowIterator = d->begin();
	
	if(testRowIterator == d->end())
		BOOST_ERROR("ERROR: EMPTY DATA SET!");
	
	DataRow row = *testRowIterator;
	BOOST_CHECK(row.getValues()[0] == 5.1f);
	BOOST_CHECK(row.getValues()[1] == 3.5f);
	BOOST_CHECK(row.getValues()[2] == 1.4f);
	BOOST_CHECK(row.getValues()[3] == 0.2f);
	
	int rowCount = 0;
	while (testRowIterator != d->end())
	{
		DataRow row = *testRowIterator;
		testRowIterator++;
		rowCount++;
		
	}
	
	BOOST_CHECK(rowCount == 150);
}

BOOST_AUTO_TEST_CASE( testingDataCSVDataLoading )
{
	ReaderFactory f;
	f.registerReader("CSV",new ReaderCSV());
	Reader* myReader=f.create("CSV");
	
	Data* d;
	ifstream myfile ("test_helpers/iris.csv");
	d = myReader->read(myfile);
	
	testData(d);
}

BOOST_AUTO_TEST_CASE( testingDataARFFDataLoading )
{
	ReaderFactory f;
	f.registerReader("ARFF",new ReaderARFF());
	Reader* myReader=f.create("ARFF");
	
	Data* d;
	ifstream myfile ("test_helpers/iris.arff");
	d = myReader->read(myfile);

	testData(d);
}

class TestHelperNormalModel : public NormalModel
{
public:
	virtual StrValuesMap& getVariances() { return NormalModel::variances; };
	virtual StrValuesMap& getAverages() { return NormalModel::averages; };
};

BOOST_AUTO_TEST_CASE( testingNormalModel )
{
	ReaderFactory f;
	f.registerReader("CSV",new ReaderCSV());
	Reader* myReader = f.create("CSV");
	
	Data* d;
	ifstream myfile ("test_helpers/iris.csv");
	d = myReader->read(myfile);
	
	BOOST_CHECK(d->begin() != d->end());
	
	int misclassified = 0;
	
	TestHelperNormalModel nm;
	NaiveBayes nb;
	nm.setTrainSet(d);
	nm.train();
	nb.setModel(&nm);
	nb.setTestSet(d);
	std::vector<std::string> testRes = nb.eval();
	
	int rowNo = 0;
	Data::iterator testRowIterator = d->begin();
	while (testRowIterator != d->end())
	{
		DataRow row = *testRowIterator;
		if (row.getLabel() != testRes[rowNo])
			misclassified ++;
		testRowIterator++;
		rowNo++;
	}
	//std::cout << misclassified << std::endl;
	BOOST_CHECK(misclassified < 15); //pozwalamy na 10% błąd klasyfikacji, efektywnie 6/150 błędnie sklasyfikowanych
}



/*

 */

test_suite* init_unit_test_suite( int, char* [] ) {
	test_suite* test= BOOST_TEST_SUITE( "testingReaderFactory" );

	return test;
}

