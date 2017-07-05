#include "stdafx.h"
//#include "effectManager.h"
//#include "effect.h"
//
//effectManager::effectManager()
//{
//}
//
//
//effectManager::~effectManager()
//{
//}
//
//HRESULT effectManager::init()
//{
//	return S_OK;
//}
//
//void effectManager::release()
//{
//	iterTotalEffect vIter;
//	iterEffect mIter;
//
//	//이펙트를 모두 넣어준 벡터를 검사
//	vIter = _vTotalEffects.begin();
//
//	for (; vIter != _vTotalEffects.end(); ++vIter)
//	{
//		//토탈 이펙트 벡터 안에 있는 맵의 이펙트 키 검사
//		mIter = vIter->begin();
//		for (; mIter != vIter->end(); )
//		{
//			if (mIter->second.size() != 0)
//			{
//				iterEffects vArrIter = mIter->second.begin();
//				for (vArrIter; vArrIter != mIter->second.end(); ++vArrIter)
//				{
//					(*vArrIter)->release();
//					delete *vArrIter;
//					vArrIter = mIter->second.erase(vArrIter);
//				}
//			}
//			else
//			{
//				++mIter;
//			}
//		}
//	}
//}
//
//void effectManager::update()
//{
//	iterTotalEffect vIter;
//	iterEffect mIter;
//
//	//이펙트를 모두 넣어준 벡터를 검사
//	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); vIter++)
//	{
//		//토탈 이펙트 벡터 안에 있는 맵의 이펙트 키 검사하자
//		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
//		{
//			iterEffects vArrIter;
//			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
//			{
//				(*vArrIter)->update();
//			}
//		}
//	}
//}
//
//void effectManager::render()
//{
//	iterTotalEffect vIter;
//	iterEffect mIter;
//
//	//이펙트를 모두 넣어준 벡터를 검사
//	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); vIter++)
//	{
//		//토탈 이펙트 벡터 안에 있는 맵의 이펙트 키 검사하자
//		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
//		{
//			iterEffects vArrIter;
//			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
//			{
//				(*vArrIter)->render();
//			}
//		}
//	}
//}
//
//void effectManager::addEffect(string effectName, const char * imageName, int imageWidth, int imageHeight, int effectWidth, int effectHeight, int fps, float elapsedTime, int buffer)
//{
//	image* img;
//	arrEffects vEffectBuffer;	//이펙트 버퍼 벡터
//	arrEffect mArrEffect;		//키 값과 이펙트 버퍼 담아줄 맵
//
//	//등록된 이미지가 매니져에 이미 있으면
//	if (IMAGEMANAGER->findImage(imageName))
//	{
//		img = IMAGEMANAGER->findImage(imageName);
//	}
//	//없으면
//	else
//	{
//		//이미지 등록
//		img = IMAGEMANAGER->addImage(imageName, imageName, imageWidth, imageHeight, true, RGB(255, 0, 255));
//	}
//
//	//총 버퍼 갯수만큼 벡터에 담아주자
//	for (int i = 0; i < buffer; i++)
//	{
//		vEffectBuffer.push_back(new effect);
//		vEffectBuffer[i]->init(img, effectWidth, effectHeight, fps, elapsedTime);
//	}
//
//	//이펙트 버퍼를 맵에 담아주자
//	mArrEffect.insert(pair<string, arrEffects>(effectName, vEffectBuffer));
//
//	//키 값과 버퍼를 담은 맵을 토탈벡터에 담아준다
//	_vTotalEffects.push_back(mArrEffect);
//}
//
//void effectManager::play(string effectName, int x, int y)
//{
//	iterTotalEffect vIter;
//	iterEffect mIter;
//
//	//이펙트를 모두 넣어준 벡터를 검사하자
//	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
//	{
//		//토탈 이펙트 벡터 안에 있는 맵의 이펙트 키 검사하자
//		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
//		{
//			//이펙트 이름과 비교해서 같지 않으면 다음 맵으로 넘어가자
//			if (!(mIter->first == effectName)) break;
//
//			//이펙트 키와 일치하면 이펙트를 실행시킨다
//			iterEffects vArrIter;
//			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
//			{
//				//이펙트 터트려주자
//				//미리 이펙트가 활성화 되어 있으면 다음걸 터트려주자
//				if ((*vArrIter)->getIsRunning()) continue;
//				(*vArrIter)->startEffect(x, y);
//				return;
//			}
//		}
//	}
//}
