#pragma once
#include "singleton.h"
class cRenderManager : public singleton<cRenderManager>
{
public:
	struct sVertexType
	{
		Vec3 pos;
		Vec2 m_uv;

		inline static constexpr DWORD FvF = D3DFVF_XYZ | D3DFVF_TEX1;
	};

	cRenderManager();
	~cRenderManager();

	LPDIRECT3DVERTEXBUFFER9 m_vb;
	LPDIRECT3DINDEXBUFFER9 m_ib;

	Vec3 m_camPos;
	Vec3 m_camLook;
	Vec3 m_camUp;
	Vec3 m_projPos;

	D3DXMATRIXA16 matView;
	D3DXMATRIXA16 matProj;

	void RefreshCamera();
	void RefreshBuffer();
	void CenterRender(cTexture* ptr, Vec2 pos, float rot = 0.f, float size = 1.f, float z = 0.f);
};

#define RENDER cRenderManager::GetInstance()