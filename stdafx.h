#pragma once

#include <vector>
#include <map>
#include <list>
#include <algorithm>
#include <string>
#include <math.h>
#include <fstream>
#include <iostream>
#include <functional>
#include <time.h>
#include "SDKsound.h"
#include "SDKwavefile.h"

#pragma comment (lib, "dsound.lib")

using namespace std;
using Vec2 = D3DXVECTOR2;
using Vec3 = D3DXVECTOR3;

#define g_device DXUTGetD3D9Device()
#define Delta DXUTGetElapsedTime()

const int WINSIZEX = 1920;
const int WINSIZEY = 1080;

#include "cTexture.h"
#include "cScene.h"
#include "cTimer.h"
#include "cParticle.h"

#include "cImageManager.h"
#include "cInputManager.h"
#include "cUIManager.h"
#include "cSceneManager.h"
#include "cRenderManager.h"
#include "cSoundManager.h"
#include "cParticleManager.h"