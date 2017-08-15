#include "stdafx.h"
#include "Battle_UnitParser.h"
#include "Battle_UnitSystem.h"

CBattle_UnitParser::CBattle_UnitParser()
{
}


CBattle_UnitParser::~CBattle_UnitParser()
{
}

std::vector<std::string> CBattle_UnitParser::loadShipData(std::string shipName)
{
	auto vData = TXTDATA_PARSER->loadDataToArray(shipName);
	return recogShipData(vData);
}

std::vector<std::string> CBattle_UnitParser::recogShipData(std::vector<std::string> vArray)
{
	if (vArray.size() <= 0)
		return std::vector<std::string>();

	std::vector<std::string> vData;

	for (auto iter : vArray)
	{
		if (iter.compare(UnitParserNS::DATA_BEGIN_KEY + " " + UnitParserNS::SHIP_DATA_KEY) == false)
			continue;
		else if (iter.compare(UnitParserNS::SHIP_DATA_KEY + " " + UnitParserNS::DATA_END_KEY) == false)
			continue;

		vData.emplace_back(iter);
	}

	return setupShipData(vData);
}

std::vector<std::string> CBattle_UnitParser::setupShipData(std::vector<std::string> vArray)
{
	int dataNumber = 0;
	std::vector<std::string> vResult;

	vResult.emplace_back(vArray[dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Ship ID				함선 ID
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + TextureKey			함선 텍스쳐 키(텍스쳐 이름)
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + TextureTop			함선 Top 갯수
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + TextureBody			함선 Body 갯수
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + TextureBottom			함선 Bottom 갯수
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Ship Name				함선 고유이름
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Ship Type				함선 타입
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Unit Type				유닛 타입
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Max HP(DP)			체력
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Repair_Speed			수리 속도
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Rotate_Speed			회전 속도
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Accelerate_Speed		엔진 가속도
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Max_Speed				최고 속도
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Rader					시야 범위(감지 범위)
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Turret_Capacity		함포 갯수
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Turret_ID				함포 ID
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Aircraft_Capacity		항공기 탑재 갯수
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Performance			퍼포먼스 게이지
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Sailor				수병 숫자
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + AntiAir_Capacity		대공포 갯수
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + AntiAir_Range			대공포 사거리
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + AntiAir_Damage		대공포 공격력
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Phase					함선 전투 Phase Number
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Mass					함선 질량(Weight)
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Evasion				함선 타겟 범위(Evasion Radius)
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + ShipRankMark			함선 계급장
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + SukenSound			함선 침몰 사운드 이름
																							//   #  + Skill					함선 스킬

	return vResult;
}
