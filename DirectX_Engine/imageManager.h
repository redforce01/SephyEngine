#ifndef _IMAGEMANAGER_H
#define _IMAGEMANAGER_H

class ImageManager;

#include "cSingletonBase.h"
#include "textureManager.h"
#include <vector>
#include <map>
#include <thread>
#include <string>
#include <tuple>

struct stTextureInfo
{
	bool loaded;
	TextureManager* texture;
	std::string texturePath;
};

class ImageManager : public cSingletonBase<ImageManager>
{
private:
	bool initialized;
	Graphics* graphics;
	
	std::thread loadingThread;
	
	typedef std::map<std::string, stTextureInfo> MAP_TEXTURE;

// IMAGE CONTAINER map<key, vector<texture>>
private:
	MAP_TEXTURE				arrTexture;
	MAP_TEXTURE::iterator	iterTexture;

public:
	ImageManager();
	~ImageManager();

	bool initialize(Graphics *graphics);
	void release();
	TextureManager* getTexture(std::string textureName);

	bool getInitialized() { return initialized; }
	void printAllTexture();

	static void LoadingTexture();
};

#define IMAGEMANAGER ImageManager::GetInstance() 
#endif // !_IMAGEMANAGER_H