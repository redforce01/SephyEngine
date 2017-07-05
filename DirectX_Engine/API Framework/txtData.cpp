#include "stdafx.h"
#include "txtData.h"


txtData::txtData()
{
}


txtData::~txtData()
{
}


HRESULT txtData::init()
{
	return S_OK;
}

void txtData::release()
{

}

//세이브
void txtData::txtSave(const char* saveFileName, vector<string> vStr)
{
	HANDLE file;

	char str[128];
	DWORD write;

	strncpy_s(str, 128, vectorArrayCombine(vStr), 126);

	//파일 생성
	file = CreateFile(saveFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);

	//파일에 쓰기
	WriteFile(file, str, 128, &write, NULL);

	CloseHandle(file);
}

char* txtData::vectorArrayCombine(vector<string> vArray)
{
	char str[128];

	ZeroMemory(str, sizeof(str));

	for (int i = 0; i < vArray.size(); i++)
	{
		strncat_s(str, 128, vArray[i].c_str(), 126);
		if (i + 1 < vArray.size()) strcat_s(str, ",");
	}

	return str;
}


//로드
vector<string> txtData::txtLoad(const char* loadFileName)
{
	HANDLE file;

	char str[65536];
	DWORD read;

	memset(str, 0, sizeof(str));

	file = CreateFile(loadFileName, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, 65536, &read, NULL);
	CloseHandle(file);

	return charArraySeparation(str);
}

vector<string> txtData::charArraySeparation(char charArray[])
{
	vector<string> vArray;

	char* temp;
	char* separator = { ", \t\n?\r" };
	char* token;

	//char *seper1 = "//Name/Class/DP/Weight";
	//char *seper2 = "//ArmorPoint/Top/Bottom/Inch";
	//char *seper3 = "//FCSName/Detection/Distance/Accuracy";
	//char *seper4 = "//EngineName/Power/MinSpeed/MaxSpeed";
	//char *seper5 = "//KeyFWidth/FHeight";
	//char *seper6 = "//KeyHWidth/HHeight";
	//char *seper7 = "//TurretSize/Distance";
	
	//strcat_s(separator, 65536, seper1);
	//strcat_s(separator, 65536, seper2);
	//strcat_s(separator, 65536, seper3);
	//strcat_s(separator, 65536, seper4);
	//strcat_s(separator, 65536, seper5);
	//strcat_s(separator, 65536, seper6);
	//strcat_s(separator, 65536, seper7);
	
	token = strtok_s(charArray, separator, &temp);
	//token = strtok_s(charArray, seper1, &temp);
	//token = strtok_s(charArray, seper2, &temp);
	//token = strtok_s(charArray, seper3, &temp);
	//token = strtok_s(charArray, seper4, &temp);
	//token = strtok_s(charArray, seper5, &temp);
	//token = strtok_s(charArray, seper6, &temp);
	//token = strtok_s(charArray, seper7, &temp);

	vArray.push_back(token);

	while (NULL != (token = strtok_s(NULL, separator, &temp)))
	{
		vArray.push_back(token);
	}

	return vArray;
}