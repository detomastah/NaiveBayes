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
	void setTrainSet(Data *trainSet);
	void setModel(ProbabilityModel *model);
	void train();
private:
	Data *trainSet;
	ProbabilityModel *model;
	StrFloatMap labelProbs;
};

class ProbabilityModel
{
public:
	void setTrainSet(Data *trainSet) { this->trainSet = trainSet; };
	virtual void train() = 0;
	virtual float getProbability(DataRow *dp, std::string label) = 0;
protected:
	Data *trainSet;
};

class NormalModel : public ProbabilityModel
{
public:
	virtual void train();
	virtual float getProbability(DataRow *dp, std::string label);
protected:
	StrValuesMap variances;
	StrValuesMap averages;
};
#endif
