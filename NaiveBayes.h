#ifndef NAIVE_BAYES_H_
#define NAIVE_BAYES_H_

#include "Data.h"
#include <map>
#include <string>
#include <valarray>

class DataRow;
class ProbabilityModel;

typedef std::map<std::string, float> StrFloatMap;
typedef std::map<std::string, std::vector<float> > StrValuesMap;

class NaiveBayes
{
public:
	void setTestSet(Data *testSet);
	void setModel(ProbabilityModel *model);
	void eval();
private:
	Data *testSet;
	ProbabilityModel *model;
};

class ProbabilityModel
{
public:
	void setTrainSet(Data *trainSet);
	void train();
	virtual float getProbability(DataRow *dp, std::string label) = 0;
protected:
	virtual void trainModel() = 0;
	Data *trainSet;
	StrFloatMap labelProbs;
};

class NormalModel : public ProbabilityModel
{
public:
	virtual float getProbability(DataRow *dp, std::string label);
protected:
	virtual void trainModel();
	StrValuesMap variances;
	StrValuesMap averages;
};
#endif
