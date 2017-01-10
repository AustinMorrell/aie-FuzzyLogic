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
		m_waterValue.setMinMaxValues(0, 20);
		m_waterValue.setValue(getWaterValue());
		UtilityScore* pWaterScore = new UtilityScore();
		pWaterScore->addUtilityValue(&m_waterValue, 1.0f);
		m_pUtilityScoreMap["collectWater"] = pWaterScore;
	}
	~UtilityNPC();

protected:
	void selectAction(float a_fdeltaTime) override;

private:
	UtilityValue m_waterValue;
	std::map<std::string, UtilityScore*> m_pUtilityScoreMap;

};

void UtilityNPC::selectAction(float a_fdeltaTime)
{
	m_waterValue.setValue(getWaterValue());
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

	if (strBestAction == "collectWater")
	{
		collectWater(a_fdeltaTime);
	}
}