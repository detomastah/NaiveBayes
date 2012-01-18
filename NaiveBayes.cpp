#include "NaiveBayes.h"
#include <iostream>
#include <cstdio>
#include <boost/lexical_cast.hpp>
#include <cmath>

std::string inspect(std::vector<float> &v)
{
	std::string retVal = std::string("[");
	for (std::vector<float>::iterator it = v.begin(); it != v.end(); it++)
		retVal += boost::lexical_cast<std::string>(*it) + std::string(", ");
	return retVal + std::string("]");
}

std::string inspect(StrValuesMap &map) 
{
	std::string retVal = "(";
	for (StrValuesMap::iterator it = map.begin(); it != map.end(); it++)
	{
		retVal += std::string(it->first) + std::string(": ") + inspect(it->second) + std::string(", ");
	}
	return retVal + ")";
}

std::string inspect(StrFloatMap &map) 
{
	std::string retVal = "(";
	for (StrFloatMap::iterator it = map.begin(); it != map.end(); it++)
	{
		retVal += std::string(it->first) + ": " + boost::lexical_cast<std::string>(it->second) + std::string(", ");
	}
	return retVal + ")";
}

void NaiveBayes::setTestSet(Data *testSet) 
{
	this->testSet = testSet; 
}

void NaiveBayes::setModel(ProbabilityModel *model) 
{
	 this->model = model;
}

std::vector<std::string> NaiveBayes::eval()
{
	std::vector<std::string> results;
	for (Data::iterator rowIt = testSet->begin(); rowIt != testSet->end() ; rowIt++)
	{
		DataRow &row = *rowIt;
		StrVector labels = this->model->getLabels();
		std::string maxLabel = labels[0];
		float maxProb = 0.0f;
		for (StrVector::iterator labelIt = labels.begin(); labelIt != labels.end(); labelIt++)
		{
			float prob = this->model->getProbability(&row, *labelIt);
			if (prob > maxProb)
			{
				maxProb = prob;
				maxLabel = *labelIt;
			}
		}
		results.push_back(maxLabel);
	}
	return results;
}

void ProbabilityModel::setTrainSet(Data *trainSet) 
{
	this->trainSet = trainSet;
}

StrVector ProbabilityModel::getLabels()
{
	StrVector result;
	for (StrFloatMap::iterator it = labelProbs.begin(); it != labelProbs.end(); it++)
		result.push_back(it->first);
	return result;
}

float ProbabilityModel::getProbability(DataRow *dp, std::string label) {
	return labelProbs[label] * getModelProbability(dp, label);
}

void ProbabilityModel::train()
{

	//zliczanie ilości rekordów o danej klasie
	float rowCount = 0.0f;
	for (Data::iterator rowIt = trainSet->begin(); rowIt != trainSet->end() ; rowIt++)
	{
		DataRow &row = *rowIt;
		if (labelProbs.find(row.getLabel()) == labelProbs.end())
			labelProbs[row.getLabel()] = 1.0f;
		else
			labelProbs[row.getLabel()] += 1.0f;
		rowCount += 1.0f;
	}

	for (StrFloatMap::iterator it=labelProbs.begin() ; it != labelProbs.end(); it++)
	{
		(*it).second = (*it).second / rowCount;
		//std::cout << (*it).second << "\n";
	}

	trainModel();
}

void NormalModel::trainModel() 
{
	StrFloatMap labelCounts;
	StrValuesMap sums;
	float rowCount = 0.0f;
	//zliczamy sumy kolumnowo dla każdej z klas
	for (Data::iterator rowIt = trainSet->begin(); rowIt != trainSet->end() ; rowIt++)
	{
		DataRow &row = *rowIt;
		if (labelCounts.find(row.getLabel()) == labelCounts.end())
		{
			labelCounts[row.getLabel()] = 1.0f;
			sums[row.getLabel()] = std::vector<float>(row.getValues());
		}
		else
		{
			labelCounts[row.getLabel()] += 1.0f;
			for (int i=0; i < row.getValues().size(); i++)
			{
				sums[row.getLabel()][i] += row.getValues()[i];
			}
		}
		rowCount += 1.0f;
	}
	
	//dzielimy sumy  przez ilość wierszy danej klasy
	for (StrValuesMap::iterator it = sums.begin(); it != sums.end(); it++)
	{
		averages[it->first] = std::vector<float>(it->second.size());
		for (int i=0; i < it->second.size(); i++)
			averages[it->first][i] = sums[it->first][i] / labelCounts[it->first];
	}
			
	//obliczamy wariancję
	for (StrValuesMap::iterator it = sums.begin(); it != sums.end(); it++)
	{
		std::string label = it->first;
		std::vector<float> &values = it->second; 
		variances[label] = std::vector<float>(values.size());
		for (int i=0; i < values.size(); i++)
		{
			variances[label][i] = 0.0f;
			for (Data::iterator rowIt = trainSet->begin(); rowIt != trainSet->end() ; rowIt++)
			{
				if ((*rowIt).getLabel() == label)
				{
					float cum = powf((*rowIt).getValues()[i] - averages[label][i], 2);
					variances[label][i] += cum;
				}
			}
			variances[label][i] /= labelCounts[label];
			
		}
	}
	//std::cout << inspect(variances) << std::endl;
	//std::cout << inspect(averages) << std::endl;
}

float NormalModel::getModelProbability(DataRow *dp, std::string label)
{
	std::vector<float> average = averages[label];
	std::vector<float> variance = variances[label];
	float probability = 1.0f;
	for (int i=0; i < average.size(); i++)
	{
		float y = powf(dp->getValues()[i] - average[i], 2.0f) / (2.0f * variance[i]);
		float z = sqrtf(2.0f * 3.14f * variance[i]);
		//std::cout << exp(-y) / z << std::endl;
		probability *= exp(-y) / z;
	}
	return probability;
}
