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

	vResult.emplace_back(vArray[dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Ship ID				�Լ� ID
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + TextureKey			�Լ� �ؽ��� Ű(�ؽ��� �̸�)
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + TextureTop			�Լ� Top ����
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + TextureBody			�Լ� Body ����
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + TextureBottom			�Լ� Bottom ����
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Ship Name				�Լ� �����̸�
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Ship Type				�Լ� Ÿ��
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Unit Type				���� Ÿ��
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Max HP(DP)			ü��
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Repair_Speed			���� �ӵ�
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Rotate_Speed			ȸ�� �ӵ�
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Accelerate_Speed		���� ���ӵ�
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Max_Speed				�ְ� �ӵ�
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Rader					�þ� ����(���� ����)
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Turret_Capacity		���� ����
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Turret_ID				���� ID
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Aircraft_Capacity		�װ��� ž�� ����
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Performance			�����ս� ������
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Sailor				���� ����
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + AntiAir_Capacity		����� ����
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + AntiAir_Range			����� ��Ÿ�
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + AntiAir_Damage		����� ���ݷ�
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Phase					�Լ� ���� Phase Number
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Mass					�Լ� ����(Weight)
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Evasion				�Լ� Ÿ�� ����(Evasion Radius)
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + ShipRankMark			�Լ� �����
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + SukenSound			�Լ� ħ�� ���� �̸�
																							//   #  + Skill					�Լ� ��ų

	return vResult;
}
