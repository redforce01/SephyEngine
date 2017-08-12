#ifndef _FILEMANAGER_H
#define _FILEMANAGER_H

class FileManager;

#include "cSingletonBase.h"

#include <string>
#include <map>
#include <vector>

struct stFile
{
	std::string path;
	std::string fullPath;
	std::string projectPath;
	std::string fileName;
	std::string ext;
	std::string parentDir;
};

namespace fileManagerNS
{
	const std::string imgExt[] = { "jpg", "JPG", "jpeg", "JPEG", "bmp", "BMP", "png", "PNG", "gif", "GIF", "tga", "TGA" };
	const std::string dataExt[] = { "txt", "TXT", "xml", "XML", "json", "JSON", "sql", "SQL" ,"mdf", "MDF" };
	const std::string soundExt[] = { "wav", "WAV", "mp3", "MP3" };
}

class FileManager : public cSingletonBase<FileManager>
{
private:
	//Vector Container vector<stFileStruct>
	typedef std::vector<stFile*>				arrFileList;
	typedef std::vector<stFile*>::iterator		iterFileList;
	
	// !!----- Not Using Container -----!!
	//string Value for FileManager - Map <KeyValue>
	//typedef std::string folderName;
	//std::map<std::string, stFile*> typedef MAP_FILE;

private:
	bool initialized;

	std::map<std::string, arrFileList*>				arrFile;
	std::map<std::string, arrFileList*>::iterator	iterFile;

	// !!----- Not Using Container -----!!
	//MAP_FILE				arrMapImage;
	//MAP_FILE::iterator	iterMapImage;

	std::vector<stFile*>				arrImage;
	std::vector<stFile*>::iterator		iterImage;

	std::vector<stFile*>				arrData;
	std::vector<stFile*>::iterator		iterData;

	std::vector<stFile*>				arrEtc;
	std::vector<stFile*>::iterator		iterEtc;

	std::vector<stFile*>				arrSound;
	std::vector<stFile*>::iterator		iterSound;

public:
	FileManager();
	~FileManager();

	HRESULT initialize();
	void release();

	void funcFindItem(char* path);
	void funcFindResource(char* path);
	void funcCheckResource(char* path);
	void funcBackDir();
	void setRootDir(std::string rootPath);
	std::string getCurrentSystemDir();

//FILEMANAGER File Seperator Functions
private:
	std::string getFilePath(std::string path);
	std::string getFileFullPath(std::string path, std::string file);
	std::string getCutProjectPath(std::string path, std::string file);
	std::string getFileName(std::string path);
	std::string getFileExtension(std::string path);
	std::string getLastDir(std::string path);

//FILEMANAGER Print Functions
private:
	void printAllFile();
	void printAllImage();
	void printAllData();
	void printAllEtc();

//File Classify Extension Functions
private:
	void funcRecognize();
	bool funcRecogImage(std::string extension);
	bool funcRecogData(std::string extension);
	bool funcRecogSound(std::string extension);
	void funcRecogEtc(stFile* file);

//File Manager Getter Functions
public:	
	inline std::map<std::string, arrFileList*>				getAllFile() { return arrFile; }
	inline std::map<std::string, arrFileList*>::iterator	getAllFileIter() { return iterFile; }

	inline std::vector<stFile*>				getAllImageFile() { return arrImage; }
	inline std::vector<stFile*>::iterator	getAllImageIter() { return iterImage; }

	inline std::vector<stFile*>				getAllDataFile() { return arrData; }
	inline std::vector<stFile*>::iterator	getAllDataIter() { return iterData; }

	inline std::vector<stFile*>				getAllEtcFile() { return arrEtc; }
	inline std::vector<stFile*>::iterator	getAllEtcIter() { return iterEtc; }

	inline std::vector<stFile*>				getAllSoundFile() { return arrSound; }
	inline std::vector<stFile*>::iterator	getAllSoundIter() { return iterSound; }
	
// Get Size Function
	inline UINT	getAllFileSize() const
	{ 
		return arrFile.size();
	}

	inline UINT	getAllImageSize() const
	{ 
		return arrImage.size();
	}

	inline UINT	getAllDataSize() const
	{ 
		return arrData.size();
	}

	inline UINT	getAllSoundSize() const
	{ 
		return arrSound.size();
	}

	inline UINT	getAllEtcSize() const
	{ 
		return arrEtc.size();
	}

	inline arrFileList*	getFileListInFolder(std::string keyFolder) const
	{ 
		return arrFile.find(keyFolder.c_str())->second;
	}

	inline stFile* getFile(std::string keyFolder, int index) const
	{ 
		return arrFile.find(keyFolder.c_str())->second->at(index);
	}

	inline stFile* getFile(std::string keyFolder, std::string fileName);
	inline std::vector<std::string>	getFolderList();
	inline std::vector<stFile*>		getFileList();

	// GET IMAGE FILE - use std::string
	inline stFile* getImageFile(std::string fileName) const
	{
		for (auto iter : arrImage)
		{
			if (iter->fileName.compare(fileName) == false)
				return iter;
		}

		return nullptr;
	}
	// GET IMAGE FILE - use Index
	inline stFile* getImageFile(int fileNum) const
	{ return arrImage[fileNum]; }

	// GET DATA FILE - use std::string
	inline stFile* getDataFile(std::string fileName) const
	{
		for (auto iter : arrData)
		{
			if (iter->fileName.compare(fileName) == false)
				return iter;
		}
	}
	// GET DATA FILE - use Index
	inline stFile* getDataFile(int fileNum) const
	{ 
		return arrData[fileNum];
	}

	inline stFile* getSoundFile(std::string fileName) const
	{
		for (auto iter : arrData)
		{
			if (iter->fileName.compare(fileName) == false)
				return iter;
		}
	}

	inline stFile* getSoundFile(int fileNum) const
	{
		return arrSound[fileNum];
	}

	// GET ETC FILE - use std::string
	inline stFile* getEtcFile(std::string fileName) const
	{
		for (auto iter : arrEtc)
		{
			if (iter->fileName.compare(fileName) == false)
				return iter;
		}
	}

	// GET ETC FILE - use index
	inline stFile* getEtcFile(int fileNum) const
	{ 
		return arrEtc[fileNum];
	}

	// GET FILE MANAGER INITIALIZED FLAG
	inline bool getInitialized() const
	{ 
		return initialized;
	}
};

#define FILEMANAGER FileManager::GetInstance()
#endif // !_FILEMANAGER_H