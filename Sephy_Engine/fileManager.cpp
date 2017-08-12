#include "stdafx.h"
#include "FileManager.h"


FileManager::FileManager() : initialized(FALSE)
{
}


FileManager::~FileManager()
{
	release();
}

HRESULT FileManager::initialize()
{
	char path[MAX_PATH];
	::GetCurrentDirectory(MAX_PATH, path);

	ENGINE_BOOT_LOG->setLog("FileSystem initialize Start");
	//function Find Resource Folder Files
	funcFindResource(path);

	//function Recognize All File
	funcRecognize();
	
	//Print File Struct
	printAllFile();
	printAllImage();
	printAllData();
	printAllEtc();

	FILEMANAGER->funcBackDir();
	ENGINE_BOOT_LOG->setLog("FileSystem initialize Complete");
	initialized = true;

	return S_OK;
}

void FileManager::release()
{
	for (auto iter : arrFile)
	{
		SAFE_DELETE(iter.second);
		
		auto sIter = iter.second->begin();
		for (sIter; sIter != iter.second->end(); sIter++)
		{			
			SAFE_DELETE((*sIter));
		}
		iter.second->clear();
	}
	arrFile.clear();
}

void FileManager::funcFindItem(char * path)
{
	char localPath[MAX_PATH];
	::GetCurrentDirectory(MAX_PATH, path);
	char resPath[MAX_PATH];
	sprintf_s(resPath, "%s%s", localPath, path);
	::SetCurrentDirectory(resPath);
	funcCheckResource(resPath);
}

void FileManager::funcFindResource(char* path)
{
	ENGINE_BOOT_LOG->setLog("Finding Resources Folder");
	char resPath[MAX_PATH];
	sprintf_s(resPath, "%s%s", path, "\\Resources");
	::SetCurrentDirectory(resPath);
	funcCheckResource(resPath);
}

void FileManager::funcCheckResource(char * path)
{
	ENGINE_BOOT_LOG->setLog("Resources Folder Recognize Start");
	HANDLE hSrch;
	WIN32_FIND_DATA wfd;
	BOOL bResult = TRUE;
	char drive[_MAX_DRIVE];
	char dir[MAX_PATH];
	char newpath[MAX_PATH];

	hSrch = FindFirstFile(path, &wfd);
	if (hSrch == INVALID_HANDLE_VALUE) {
		return;
	}
	_splitpath_s(path, drive, _MAX_DRIVE, dir, MAX_PATH, NULL, NULL, NULL, NULL);
	while (bResult) {
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			if (strcmp(wfd.cFileName, ".") && strcmp(wfd.cFileName, "..")) {
				arrFileList* temp = new arrFileList;
				std::string keyName = wfd.cFileName;
				arrFile.emplace(keyName, temp);
				sprintf_s(newpath, "%s%s%s\\*.*", drive, dir, wfd.cFileName);
				funcCheckResource(newpath);
			}
		}
		else
		{
			char myPath[MAX_PATH];
			sprintf_s(myPath, "%s%s", drive, dir);
			stFile* temp = new stFile;
			//ZeroMemory(&temp, sizeof(temp));

			temp->path			= getFilePath(myPath);
			temp->fullPath		= getFileFullPath(myPath, wfd.cFileName);
			temp->projectPath	= getCutProjectPath(myPath, wfd.cFileName);
			temp->fileName		= getFileName(wfd.cFileName);
			temp->ext			= getFileExtension(wfd.cFileName);
			temp->parentDir		= getLastDir(dir);
			
			arrFile.find(temp->parentDir.c_str())->second->emplace_back(temp);
			ENGINE_BOOT_LOG->setLog(temp->fileName + " Uploaded");
		}

		bResult = FindNextFile(hSrch, &wfd);
	}

	FindClose(hSrch);
}

void FileManager::funcBackDir()
{
	char path[MAX_PATH] = { 0, };
	::GetCurrentDirectory(MAX_PATH, path);

	int i = _tcslen(path) - 1;
	while (i >= 0 && path[i] != '\\') i--;
	if (i <= 0) return;
	path[i] = 0;
	::SetCurrentDirectory((LPCTSTR)path);
}

void FileManager::setRootDir(std::string rootPath)
{
	::SetCurrentDirectory(rootPath.c_str());
}

std::string FileManager::getCurrentSystemDir()
{
	char path[MAX_PATH] = { 0, };
	::GetCurrentDirectory(MAX_PATH, path);

	return path;
}

std::string FileManager::getFilePath(std::string path)
{
	return path;
}

std::string FileManager::getFileFullPath(std::string path, std::string file)
{
	return std::string(path + file);
}

std::string FileManager::getCutProjectPath(std::string path, std::string file)
{
	std::string str = path + file;
	int point = str.rfind("Resources");
	str = str.substr(point, str.size());

	return str;
}

std::string FileManager::getFileName(std::string path)
{
	std::string strPath = path;

	int index = 0;
	for (UINT i = 0; i < strPath.size(); i++)
	{
		if (strPath[i] == '.')
		{
			index = i;
		}
	}

	strPath = strPath.substr(0, index);

	return strPath;
}

std::string FileManager::getFileExtension(std::string path)
{
	std::string strPath = path;

	int index = 0;
	index = strPath.rfind(".");
	
	if (index != 0)
	{
		strPath = strPath.substr(index + 1, strPath.size());
		return strPath;
	}

	return path;
}

std::string FileManager::getLastDir(std::string path)
{
	std::string strPath = path;
	PathStripPath((LPSTR)strPath.c_str());
	PathRemoveBackslash((LPSTR)strPath.c_str());

	return strPath;
}

void FileManager::printAllFile()
{
	printf("*********************\n");
	printf("arrFiles Size : %d\n\n", arrFile.size());
	for (iterFile = arrFile.begin(); iterFile != arrFile.end(); iterFile++)
	{
		printf("FolderName : %s\n", iterFile->first.c_str());
		printf("Folder File Size : %d\n\n", iterFile->second->size());

		iterFileList iter;
		for (iter = iterFile->second->begin(); iter != iterFile->second->end(); iter++)
		{
			printf("\n");
			printf("path : %s\n", (*iter)->path.c_str());
			printf("fileName : %s\n", (*iter)->fileName.c_str());
			printf("ext : %s\n", (*iter)->ext.c_str());
			printf("parentDir : %s\n", (*iter)->parentDir.c_str());
			printf("\n\n");
		}
	}
}

void FileManager::printAllImage()
{
	if (arrImage.size() <= 0)
	{
		printf("No Image Files\n\n");
		return;
	}

	printf("------ IMAGE LIST -----\n");
	int index = 0;
	for (iterImage = arrImage.begin(); iterImage != arrImage.end(); iterImage++)
	{
		printf("Image_%d : %s.%s\n", index, (*iterImage)->fileName.c_str(), (*iterImage)->ext.c_str());
		index++;
	}
	printf("------ IMAGE LIST END -----\n\n");
}

void FileManager::printAllData()
{
	if (arrData.size() <= 0)
	{
		printf("No DATA Files\n\n");
		return;
	}

	printf("------ DATA LIST -----\n");
	int index = 0;
	for (iterData = arrData.begin(); iterData != arrData.end(); iterData++)
	{
		printf("Data_%d : %s.%s\n", index, (*iterData)->fileName.c_str(), (*iterData)->ext.c_str());
		index++;
	}
	printf("------ DATA LIST END -----\n\n");
}

void FileManager::printAllEtc()
{
	if (arrEtc.size() <= 0)
	{
		printf("No OTHER Files\n");
		return;
	}

	printf("------ OTHER LIST -----\n");
	int index = 0;
	for (iterEtc = arrEtc.begin(); iterEtc != arrEtc.end(); iterEtc++)
	{
		printf("Data_%d : %s.%s\n", index, (*iterEtc)->fileName.c_str(), (*iterEtc)->ext.c_str());
		index++;
	}
	printf("------ OTHER LIST END -----\n\n");
}

void FileManager::funcRecognize()
{
	bool result = false;
	for (iterFile = arrFile.begin(); iterFile != arrFile.end(); iterFile++)
	{
		for (iterFileList iter = iterFile->second->begin(); iter != iterFile->second->end(); iter++)
		{
			std::string extension = (*iter)->ext;
			
			// Recog Image
			if (funcRecogImage(extension))
			{
				//stFile* newImageFile;
				//newImageFile->ext			= (*iter)->ext;
				//newImageFile->fileName 	= (*iter)->fileName;
				//newImageFile->parentDir	= (*iter)->parentDir;
				//newImageFile->path	 	= (*iter)->path;
				//newImageFile->fullPath 	= (*iter)->fullPath;
				//newImageFile->projectPath	= (*iter)->projectPath;
				//arrImage.emplace_back(newImageFile);

				// !!----- Not Using Container -----!!
				//arrMapImage.emplace(newImageFile.fileName, &newImageFile);

				arrImage.emplace_back((*iter));
				ENGINE_BOOT_LOG->setLog((*iter)->fileName + " Recognized");
				extension.clear();
				continue;
			}
			// Recog Data
			else if (funcRecogData(extension))
			{
				//stFile* newDataFile;
				//newDataFile->ext			= (*iter)->ext;
				//newDataFile->fileName		= (*iter)->fileName;
				//newDataFile->parentDir	= (*iter)->parentDir;
				//newDataFile->path			= (*iter)->path;
				//newDataFile->fullPath		= (*iter)->fullPath;
				//newDataFile->projectPath	= (*iter)->projectPath;
				//arrData.emplace_back(newDataFile);

				arrData.emplace_back((*iter));
				ENGINE_BOOT_LOG->setLog((*iter)->fileName + " Recognized");
				extension.clear();
				continue;
			}
			// Recog Sound
			else if (funcRecogSound(extension))
			{
				arrSound.emplace_back((*iter));
				ENGINE_BOOT_LOG->setLog((*iter)->fileName + "Recognized");
				extension.clear();
				continue;
			}
			// Recog Etc
			else
			{
				funcRecogEtc((*iter));
				ENGINE_BOOT_LOG->setLog((*iter)->fileName + " Recognized");
				extension.clear();
				continue;
			}
		}
	}
}

bool FileManager::funcRecogImage(std::string extension)
{
	for (UINT i = 0; i < sizeof(fileManagerNS::imgExt) / sizeof(std::string); i++)
	{
		if (extension.compare(fileManagerNS::imgExt[i].c_str()) == 0)
		{
			return true;
		}
	}

	return false;
}

bool FileManager::funcRecogData(std::string extension)
{
	for (UINT i = 0; i < sizeof(fileManagerNS::dataExt) / sizeof(std::string); i++)
	{
		if (extension.compare(fileManagerNS::dataExt[i].c_str()) == 0)
		{
			return true;
		}
	}

	return false;
}

bool FileManager::funcRecogSound(std::string extension)
{
	for (UINT i = 0; i < sizeof(fileManagerNS::soundExt) / sizeof(std::string); i++)
	{
		if (extension.compare(fileManagerNS::soundExt[i].c_str()) == 0)
		{
			return true;
		}
	}

	return false;
}

void FileManager::funcRecogEtc(stFile* file)
{
	arrEtc.emplace_back(file);
}

stFile* FileManager::getFile(std::string keyFolder, std::string fileName)
{
	iterFile = arrFile.find(keyFolder);
	for (iterFileList iter = iterFile->second->begin(); iter != iterFile->second->end(); iter++)
	{
		if (!strcmp((*iter)->fileName.c_str(), fileName.c_str()) )
		{
			return (*iter);
		}
	}
	
	return nullptr;
}

std::vector<std::string> FileManager::getFolderList()
{
	std::vector<std::string> vecFolder;

	std::string folderName;
	
	for (iterFile = arrFile.begin(); iterFile != arrFile.end(); iterFile++)
	{
		vecFolder.emplace_back(iterFile->first.c_str());
	}

	return vecFolder;
}

std::vector<stFile*> FileManager::getFileList()
{
	std::vector<stFile*> vecFile;

	for (iterFile = arrFile.begin(); iterFile != arrFile.end(); iterFile++)
	{
		for (iterFileList iter = iterFile->second->begin(); iter != iterFile->second->end(); iter++)
		{			
			vecFile.emplace_back((*iter));
		}
	}

	return vecFile;
}
