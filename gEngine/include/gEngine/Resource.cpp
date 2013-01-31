#include "Resource.h"
using namespace utils;



bool Resource::hlInitialized = false;

vector<Resource::sPackage*> Resource::packages;


bool Resource::cache(string file)
{
	if(file.size() <= 0) return false;

	if(!hlInitialized)
	{
		hlInitialize();
		hlInitialized = true;
	}
	
	// if(findObject(packages
	hlUInt  package = 0;
	if(!hlCreatePackage(hlGetPackageTypeFromName(file.c_str()),&package)) return false;
	hlBindPackage(package);

	if(!hlPackageOpenFile(file.c_str(),HL_MODE_READ | HL_MODE_QUICK_FILEMAPPING)) return false;

	int filesCount = hlFolderGetCount(hlPackageGetRoot());

	if(filesCount <= 0) return false;

	sPackage *s_package = new sPackage;
			  s_package->name = file;
			  packages.push_back(s_package);

	for(int i=0; i<filesCount; ++i)
	{
		HLDirectoryItem	*pItem = hlFolderGetItem(hlPackageGetRoot(),i); 

		if(hlItemGetType(pItem) == HL_ITEM_FILE)
		{					
			HLStream *pStream = 0;
			if(!hlFileCreateStream(pItem,&pStream)) return false;

			if(!hlStreamOpen(pStream,HL_MODE_READ)) return false;
			
			sFile *s_file = new sFile;
				   s_file->name = string(hlItemGetName(pItem));
				   s_file->size = hlStreamGetStreamSize(pStream);
				   s_file->data = new char[s_file->size];
				   packages[packages.size()-1]->files.push_back(s_file);

			int j = 0;
			while(hlStreamReadChar(pStream,&s_file->data[j]) && j < s_file->size) j++;
			
			hlStreamClose(pStream);
			hlFileReleaseStream(pItem,pStream);
		}
	}

	hlPackageClose();

	return true;
}

void Resource::dump(string package)
{
	for(size_t i=0; i<packages.size(); ++i)
		if(package.compare(packages[i]->name) == 0)
		{
			while(packages[i]->files.size() > 0)
			{
				delete[] packages[i]->files[0]->data;
						 packages[i]->files[0]->data = NULL;
				delete packages[i]->files[0];
					   packages[i]->files[0] = NULL;

				removeObject(packages[i]->files[0],packages[i]->files);
			}

			delete	packages[i];
					packages[i] = NULL;
			
			removeObject(packages[i],packages);

			break;
		}
}

SDL_RWops* Resource::fetch(string file)
{
	if(file.size() > 0)
		for(size_t i=0; i<packages.size(); ++i)
			for(size_t j=0; j<packages[i]->files.size(); ++j)
				if(file.compare(packages[i]->files[j]->name) == 0)
					return SDL_RWFromMem(packages[i]->files[j]->data,packages[i]->files[j]->size*sizeof(char));

	return NULL;
}