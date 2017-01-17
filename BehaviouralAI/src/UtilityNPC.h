#pragma once
#include <map>
#include "src\UtilityValue.h"
#include "src\BaseNPC.h"
#include "src\UtilityScore.h"
using namespace UtilitySystem;
using namespace std;

class UtilityNPC : public BaseNPC
{
public:
	UtilityNPC(World* pWorld) : BaseNPC(pWorld)
	{
		m_waterValue.setNormalizationType(UtilityValue::INVERSE_LINEAR);
		m_waterValue.setMinMaxValues(20, 200);
		m_waterValue.setValue(getWaterValue());
		UtilityScore* pWaterScore = new UtilityScore();
		pWaterScore->addUtilityValue(&m_waterValue, 1.0f);
		m_pUtilityScoreMap["collectWater"] = pWaterScore;

		m_foodValue.setNormalizationType(UtilityValue::INVERSE_LINEAR);
		m_foodValue.setMinMaxValues(20, 200);
		m_foodValue.setValue(getFoodValue());
		UtilityScore* pFoodScore = new UtilityScore();
		pFoodScore->addUtilityValue(&m_foodValue, 1.0f);
		m_pUtilityScoreMap["collectFood"] = pFoodScore;

		m_restValue.setNormalizationType(UtilityValue::INVERSE_LINEAR);
		m_restValue.setMinMaxValues(20, 200);
		m_restValue.setValue(getRestValue());
		UtilityScore* pRestScore = new UtilityScore();
		pRestScore->addUtilityValue(&m_restValue, 1.0f);
		m_pUtilityScoreMap["collectRest"] = pRestScore;

		m_logValue.setNormalizationType(UtilityValue::INVERSE_LINEAR);
		m_logValue.setMinMaxValues(0, 10000);
		m_logValue.setValue(getNumberOfLogs());
		UtilityScore* pLogScore = new UtilityScore();
		pLogScore->addUtilityValue(&m_logValue, 1.0f);
		m_pUtilityScoreMap["collectLog"] = pLogScore;
	}
	~UtilityNPC();

protected:
	void selectAction(float a_fdeltaTime) override;

private:
	UtilityValue m_waterValue;
	UtilityValue m_foodValue;
	UtilityValue m_restValue;
	UtilityValue m_logValue;
	UtilityValue m_buildValue;
	std::map<std::string, UtilityScore*> m_pUtilityScoreMap;

};

void UtilityNPC::selectAction(float a_fdeltaTime)
{
	m_waterValue.setValue(getWaterValue());
	m_foodValue.setValue(getFoodValue());
	m_restValue.setValue(getRestValue());
	m_logValue.setValue(getNumberOfLogs());

	float fBestScore = 0.0f;
	std::string strBestAction;
	for (auto score : m_pUtilityScoreMap)
	{
		float fThisScore = score.second->getUtilityScore();
		if (fThisScore > fBestScore)
		{
			fBestScore = fThisScore;
			strBestAction = score.first;
		}
	}

	if (getNumberOfLogs() > 2)
	{
		buildHouse(a_fdeltaTime);
	}

	else if (strBestAction == "collectWater")
	{
		collectWater(a_fdeltaTime);
	}

	else if (strBestAction == "collectFood")
	{
		collectFood(a_fdeltaTime);
	}

	else if (strBestAction == "collectRest")
	{
		rest(a_fdeltaTime);
	}

	else if (strBestAction == "collectLog")
	{
		chopTree(a_fdeltaTime);
	}
}