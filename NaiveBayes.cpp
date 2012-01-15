#include "NaiveBayes.h"
#include <iostream>
#include <cstdio>

void NaiveBayes::setTrainSet(Data *trainSet) { this->trainSet = trainSet; }

void NaiveBayes::setModel(ProbabilityModel *model) 
{
	 this->model = model;
	 this->model->setTrainSet(this->trainSet);
}

void NaiveBayes::train()
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
	
	model->train();
}

void NormalModel::train() 
{
	StrFloatMap labelCounts;
	float rowCount = 0.0f;
	//zliczamy sumy kolumnowo dla każdej z klas
	for (Data::iterator rowIt = trainSet->begin(); rowIt != trainSet->end() ; rowIt++)
	{
		DataRow &row = *rowIt;
		if (labelCounts.find(row.getLabel()) == labelCounts.end())
		{
			labelCounts[row.getLabel()] = 1.0f;
			averages[row.getLabel()] = std::vector<float>(row.getValues());
		}
		else
		{
			labelCounts[row.getLabel()] += 1.0f;
			for (int i=0; i < row.getValues().size(); i++)
			{
				averages[row.getLabel()][i] += row.getValues()[i];
			}
		}
		rowCount += 1.0f;
	}
	
	//dzielimy sumy  przez ilość wierszy danej klasy
	for (StrValuesMap::iterator it = averages.begin(); it != averages.end(); it++)
		for (int i=0; i < it->second.size(); i++)
					averages[it->first][i] /= labelCounts[it->first];
}

float NormalModel::getProbability(DataRow *dp, std::string label)
{
}
