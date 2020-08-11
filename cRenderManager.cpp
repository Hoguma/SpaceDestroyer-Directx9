#include "DXUT.h"
#include "cRenderManager.h"

cRenderManager::cRenderManager()
{
	g_device->CreateVertexBuffer(sizeof(sVertexType) * 4, D3DUSAGE_WRITEONLY, sVertexType::FvF, D3DPOOL_MANAGED, &m_vb, NULL);

	sVertexType* pVertices = nullptr;

	m_vb->Lock(0, 0, (void**)&pVertices, 0);

	pVertices[0].pos = Vec3(-0.5f, 0.5f, 0);
	pVertices[1].pos = Vec3(0.5f, 0.5f, 0);
	pVertices[2].pos = Vec3(-0.5f, -0.5f, 0);
	pVertices[3].pos = Vec3(0.5f, -0.5f, 0);

	pVertices[0].m_uv = Vec2(0, 0);
	pVertices[1].m_uv = Vec2(1, 0);
	pVertices[2].m_uv = Vec2(0, 1);
	pVertices[3].m_uv = Vec2(1, 1);

	m_vb->Unlock();

	g_device->CreateIndexBuffer(sizeof(WORD) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_ib, NULL);

	WORD idx[]{ 1,2,0,1,3,2 };

	void* pIndices = NULL;
	m_ib->Lock(0, 0, &pIndices, 0);
	memcpy(pIndices, idx, sizeof(WORD) * 6);
	m_ib->Unlock();

	g_device->SetStreamSource(0, m_vb, 0, sizeof(sVertexType));
	g_device->SetFVF(sVertexType::FvF);
	g_device->SetIndices(m_ib);

	g_device->SetRenderState(D3DRS_LIGHTING, FALSE);
	g_device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	g_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	
	RefreshCamera();
}

cRenderManager::~cRenderManager()
{
	m_vb->Release();
	m_ib->Release();
}

void cRenderManager::RefreshCamera()
{
	m_projPos = Vec3(WINSIZEX, WINSIZEY, 100);
	D3DXMatrixOrthoRH(&matProj, m_projPos.x, m_projPos.y, 0, m_projPos.z);
	g_device->SetTransform(D3DTS_PROJECTION, &matProj);

	m_camPos = Vec3(0, 0, 1);
	m_camLook = Vec3(0, 0, 0);
	m_camUp = Vec3(0, 1, 0);

	D3DXMatrixLookAtRH(&matView, &m_camPos, &m_camLook, &m_camUp);
	g_device->SetTransform(D3DTS_VIEW, &matView);
}

void cRenderManager::RefreshBuffer()
{
	g_device->CreateVertexBuffer(sizeof(sVertexType) * 4, D3DUSAGE_WRITEONLY, sVertexType::FvF, D3DPOOL_MANAGED, &m_vb, NULL);

	sVertexType* pVertices = nullptr;

	m_vb->Lock(0, 0, (void**)&pVertices, 0);

	pVertices[0].pos = Vec3(-0.5f, 0.5f, 0);
	pVertices[1].pos = Vec3(0.5f, 0.5f, 0);
	pVertices[2].pos = Vec3(-0.5f, -0.5f, 0);
	pVertices[3].pos = Vec3(0.5f, -0.5f, 0);

	pVertices[0].m_uv = Vec2(0, 0);
	pVertices[1].m_uv = Vec2(1, 0);
	pVertices[2].m_uv = Vec2(0, 1);
	pVertices[3].m_uv = Vec2(1, 1);

	m_vb->Unlock();

	g_device->CreateIndexBuffer(sizeof(WORD) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_ib, NULL);

	WORD idx[]{ 1,2,0,1,3,2 };

	void* pIndices = NULL;
	m_ib->Lock(0, 0, &pIndices, 0);
	memcpy(pIndices, idx, sizeof(WORD) * 6);
	m_ib->Unlock();

	g_device->SetStreamSource(0, m_vb, 0, sizeof(sVertexType));
	g_device->SetFVF(sVertexType::FvF);
	g_device->SetIndices(m_ib);

	g_device->SetRenderState(D3DRS_LIGHTING, FALSE);
	g_device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	g_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
}

void cRenderManager::CenterRender(cTexture* ptr, Vec2 pos, float rot, float size, float z)
{
	D3DXMATRIXA16 matPos, matScale, matRot, matWorld;
	D3DXMatrixTranslation(&matPos, pos.x - WINSIZEX / 2, -(pos.y - WINSIZEY / 2), z);
	D3DXMatrixScaling(&matScale, ptr->info.Width * size, ptr->info.Height * size, 1);
	D3DXMatrixRotationZ(&matRot, rot);
	matWorld = matScale * matRot * matPos;

	g_device->SetTransform(D3DTS_WORLD, &matWorld);
	g_device->SetTexture(0, ptr->ptr);
	g_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}
