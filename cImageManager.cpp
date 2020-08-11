#include "DXUT.h"
#include "cImageManager.h"

cImageManager::cImageManager()
{
}

cImageManager::~cImageManager()
{
    for (auto iter : m_images) { 
        iter.second->ptr->Release();
        SAFE_DELETE(iter.second); 
    }
}

cTexture* cImageManager::AddImage(const string& key, const string& path, int count)
{
    auto find = m_images.find(key);
    char Path[128];
    if (count == 0)
    {
        sprintf(Path, "./Resource/Image/%s.png", path.c_str());
        string _path = Path;
        if (find == m_images.end())
        {
            LPDIRECT3DTEXTURE9 ptr;
            D3DXIMAGE_INFO info;
            if (D3DXCreateTextureFromFileExA(g_device, _path.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0,
                D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, &info, nullptr, &ptr) == S_OK)
            {
                cTexture* temp = new cTexture(ptr, info);
                m_images.insert(make_pair(key, temp));
                return temp;
            }
            return nullptr;
        }
    }
    else
    {
        char Key[128];
        for (int i = 0; i < count; i++)
        {
            sprintf(Path, "./Resource/Image/%s (%d).png", path.c_str(), i);
            sprintf(Key, "%s%d", key.c_str(), i);
            string _path = Path;
            if (find == m_images.end())
            {
                LPDIRECT3DTEXTURE9 ptr;
                D3DXIMAGE_INFO info;
                if (D3DXCreateTextureFromFileExA(g_device, _path.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0,
                    D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, &info, nullptr, &ptr) == S_OK)
                {
                    cTexture* temp = new cTexture(ptr, info);
                    m_images.insert(make_pair(Key, temp));
                }
            }
        }
        return nullptr;
    }
    return find->second;
}

cTexture* cImageManager::FindImage(const string& key)
{
    auto find = m_images.find(key);
    if (find == m_images.end()) return nullptr;
    return find->second;
}

vector<cTexture*> cImageManager::MakeVecImg(const string& key)
{
    vector<cTexture*> vecImg;
    for (int i = 0;; i++)
    {
        char Key[128];
        sprintf(Key, "%s%d", key.c_str(), i);
        auto find = FindImage(Key);
        if (find == nullptr) break;
        vecImg.push_back(find);
    }
    return vecImg;
}
