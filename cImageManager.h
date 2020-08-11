#pragma once
#include "singleton.h"
class cImageManager :
    public singleton<cImageManager>
{
public:
    map<string, cTexture*> m_images;

    cImageManager();
    ~cImageManager();

    cTexture* AddImage(const string& key, const string& path, int count = 0);
    cTexture* FindImage(const string& key);

    vector<cTexture*> MakeVecImg(const string& key);
};

#define IMAGE cImageManager::GetInstance()