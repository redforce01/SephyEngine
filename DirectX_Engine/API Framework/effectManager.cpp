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
//	//����Ʈ�� ��� �־��� ���͸� �˻�
//	vIter = _vTotalEffects.begin();
//
//	for (; vIter != _vTotalEffects.end(); ++vIter)
//	{
//		//��Ż ����Ʈ ���� �ȿ� �ִ� ���� ����Ʈ Ű �˻�
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
//	//����Ʈ�� ��� �־��� ���͸� �˻�
//	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); vIter++)
//	{
//		//��Ż ����Ʈ ���� �ȿ� �ִ� ���� ����Ʈ Ű �˻�����
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
//	//����Ʈ�� ��� �־��� ���͸� �˻�
//	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); vIter++)
//	{
//		//��Ż ����Ʈ ���� �ȿ� �ִ� ���� ����Ʈ Ű �˻�����
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
//	arrEffects vEffectBuffer;	//����Ʈ ���� ����
//	arrEffect mArrEffect;		//Ű ���� ����Ʈ ���� ����� ��
//
//	//��ϵ� �̹����� �Ŵ����� �̹� ������
//	if (IMAGEMANAGER->findImage(imageName))
//	{
//		img = IMAGEMANAGER->findImage(imageName);
//	}
//	//������
//	else
//	{
//		//�̹��� ���
//		img = IMAGEMANAGER->addImage(imageName, imageName, imageWidth, imageHeight, true, RGB(255, 0, 255));
//	}
//
//	//�� ���� ������ŭ ���Ϳ� �������
//	for (int i = 0; i < buffer; i++)
//	{
//		vEffectBuffer.push_back(new effect);
//		vEffectBuffer[i]->init(img, effectWidth, effectHeight, fps, elapsedTime);
//	}
//
//	//����Ʈ ���۸� �ʿ� �������
//	mArrEffect.insert(pair<string, arrEffects>(effectName, vEffectBuffer));
//
//	//Ű ���� ���۸� ���� ���� ��Ż���Ϳ� ����ش�
//	_vTotalEffects.push_back(mArrEffect);
//}
//
//void effectManager::play(string effectName, int x, int y)
//{
//	iterTotalEffect vIter;
//	iterEffect mIter;
//
//	//����Ʈ�� ��� �־��� ���͸� �˻�����
//	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
//	{
//		//��Ż ����Ʈ ���� �ȿ� �ִ� ���� ����Ʈ Ű �˻�����
//		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
//		{
//			//����Ʈ �̸��� ���ؼ� ���� ������ ���� ������ �Ѿ��
//			if (!(mIter->first == effectName)) break;
//
//			//����Ʈ Ű�� ��ġ�ϸ� ����Ʈ�� �����Ų��
//			iterEffects vArrIter;
//			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
//			{
//				//����Ʈ ��Ʈ������
//				//�̸� ����Ʈ�� Ȱ��ȭ �Ǿ� ������ ������ ��Ʈ������
//				if ((*vArrIter)->getIsRunning()) continue;
//				(*vArrIter)->startEffect(x, y);
//				return;
//			}
//		}
//	}
//}
