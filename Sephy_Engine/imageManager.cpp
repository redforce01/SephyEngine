#include "stdafx.h"
#include "imageManager.h"


ImageManager::ImageManager() : initialized(FALSE)
{
}


ImageManager::~ImageManager()
{
	if(loadingThread.joinable())
		loadingThread.join();

	for (auto iter : arrTexture)
	{
		SAFE_DELETE(iter.second.texture);
	}
	arrTexture.clear();
}

bool ImageManager::initialize(Graphics *graphics)
{
	printf("ImageManager Initialize Start\n\n");
	ENGINE_BOOT_LOG->setLog("Texture ImageManager System Initialize Start");
	this->graphics = graphics;
	

	std::string imageKey;
	std::string filePath;
	stTextureInfo newTexture;

	HRESULT hr = E_FAIL;

	int size = FILEMANAGER->getAllImageSize();
	for (int i = 0; i < size; i++)
	{
		imageKey.clear();
		filePath.clear();
		ZeroMemory(&newTexture, sizeof(newTexture));

		newTexture.texture = new TextureManager;

		imageKey = FILEMANAGER->getAllImageFile()[i]->fileName;
		filePath = FILEMANAGER->getAllImageFile()[i]->projectPath;

		//newTexture.texture = new TextureManager;
		hr = newTexture.texture->initialize(g_Graphics, filePath);
		ENGINE_BOOT_LOG->setLog("Texture : " + imageKey + "initialize");
		if (newTexture.texture->getTexture() == NULL)
		{
			hr = E_FAIL;
		}

		// if texture initialize failed continue
		if (FAILED(hr))
		{
			newTexture.loaded = false;
			newTexture.texturePath = filePath;
			printf("Error! Texture Load Failed... File Name : %s\n", imageKey.c_str());
			continue;
		}

		// success texture initialize
		if (hr == S_OK || hr == S_FALSE)
		{
			newTexture.loaded = true;
			newTexture.texturePath = filePath;
			printf("Texture Load Name : %s\n", imageKey.c_str());
			IMAGEMANAGER->arrTexture.emplace(imageKey, newTexture);	//texture insert Map
			ENGINE_BOOT_LOG->setLog("Texture : " + imageKey + "Emplace Container");
		}
	}

	IMAGEMANAGER->initialized = true;

	IMAGEMANAGER->printAllTexture();
	printf("\nAll Texture Loading Finish\n");

	//loadingThread = std::thread(&LoadingTexture);


	return initialized;
}

void ImageManager::release()
{
}

TextureManager* ImageManager::getTexture(std::string textureName)
{
	std::tuple<bool, TextureManager*> result;
	bool b = arrTexture.find(textureName)->second.loaded;

	if (b == FALSE)
		return nullptr;

	TextureManager* rt;
	rt = arrTexture.find(textureName)->second.texture;

	return rt;
}

void ImageManager::printAllTexture()
{
	printf("\n----------- All Texture List ----------- \n\n");
	int textureNum = 0;
	for (iterTexture = arrTexture.begin(); iterTexture != arrTexture.end(); ++iterTexture)
	{
		printf("%d. Texture : %s\n", textureNum, iterTexture->first.c_str());
		textureNum++;
	}
}

//void ImageManager::LoadingTexture()
//{
//	std::string imageKey;
//	std::string filePath;
//	stTextureInfo newTexture;
//
//	HRESULT hr = E_FAIL;
//	
//	int size = FILEMANAGER->getAllImageSize();
//	for (int i = 0; i < size; i++)
//	{
//		imageKey.clear();
//		filePath.clear();
//		ZeroMemory(&newTexture, sizeof(newTexture));
//
//		newTexture.texture = new TextureManager;
//
//		imageKey = FILEMANAGER->getAllImageFile()[i].fileName;
//		filePath = FILEMANAGER->getAllImageFile()[i].projectPath;
//
//		//newTexture.texture = new TextureManager;
//		hr = newTexture.texture->initialize(g_Graphics, filePath);
//		
//		if (newTexture.texture->getTexture() == NULL)
//		{
//			hr = E_FAIL;
//		}
//
//		// if texture initialize failed continue
//		if (FAILED(hr))
//		{
//			newTexture.loaded = false;
//			newTexture.texturePath = filePath;
//			printf("Error! Texture Load Failed... File Name : %s\n", imageKey.c_str());
//			continue;
//		}
//
//		// success texture initialize
//		if (hr == S_OK || hr == S_FALSE)
//		{
//			newTexture.loaded = true;
//			newTexture.texturePath = filePath;
//			printf("Texture Load Name : %s\n", imageKey.c_str());
//			IMAGEMANAGER->arrTexture.emplace(imageKey, newTexture);	//texture insert Map
//		}
//	}
//
//	IMAGEMANAGER->initialized = true;
//
//#ifdef _DEBUG
//
//	IMAGEMANAGER->printAllTexture();
//	printf("\nAll Texture Loading Finish\n");
//
//#endif // _DEBUG
//}