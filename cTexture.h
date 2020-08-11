#pragma once
class cTexture
{
public:
	LPDIRECT3DTEXTURE9 ptr;
	D3DXIMAGE_INFO info;

	cTexture(LPDIRECT3DTEXTURE9 ptr, D3DXIMAGE_INFO info) : ptr(ptr), info(info) {}
};

