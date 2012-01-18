#ifndef NAIVE_BAYES_H_
#define NAIVE_BAYES_H_

#include "Data.h"
#include <map>
#include <string>
#include <valarray>

class DataRow;
class ProbabilityModel;

typedef std::map<std::string, float> StrFloatMap;
typedef std::vector<std::string> StrVector;
typedef std::map<std::string, std::vector<float> > StrValuesMap;

std::string inspect(std::vector<float> &v);
std::string inspect(StrValuesMap &map);
std::string inspect(StrFloatMap &map);

//delagacja
//klasa wykorzystujaca model prawdopodobienstwa do klasyfikacji zbioru testowego
class NaiveBayes
{
public:
	void setTestSet(Data *testSet);
	void setModel(ProbabilityModel *model);
	std::vector<std::string> eval();
private:
	Data *testSet;
	ProbabilityModel *model;
};

//klasa bazowa do obliczania parametrow modelu prawdopodobienstwa
//klasa deleguje obliczanie parametrów do klasy dziedziczącej za pomocą wzorca szablonu (template)
//a sama oblicza jedynie prawdopobienstwa 
//klasa abstrakcyjna
class ProbabilityModel
{
public:
	void setTrainSet(Data *trainSet);
	void train();
	StrVector getLabels();
	virtual float getProbability(DataRow *dp, std::string label);
protected:
	virtual void trainModel() = 0; //
	virtual float getModelProbability(DataRow *dp, std::string label) = 0; //
	Data *trainSet;
	StrFloatMap labelProbs;
};

//implementuje rozklad normalny
class NormalModel : public ProbabilityModel
{
public:
	virtual float getModelProbability(DataRow *dp, std::string label);
protected:
	virtual void trainModel();
	StrValuesMap variances;
	StrValuesMap averages;
};
#endif
