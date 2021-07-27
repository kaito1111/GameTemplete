#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <math.h>
#include <vector>
#include <list>
#include <D3Dcompiler.h>
#include <Windows.h>
#include <d3d11.h>
#include <map>
#include <functional>
#include <algorithm>
#include <xaudio2.h>
#include <x3daudio.h>
#include <xaudio2fx.h>

#include "btBulletDynamicsCommon.h"
#include "BulletCollision\CollisionDispatch\btGhostObject.h"

//DirectXTK�̃C���N���[�h�t�@�C���B
#include "DirectXTK/Inc/Model.h"
#include "DirectXTK/Inc/Effects.h"	
#include "DirectXTK/Inc/CommonStates.h"
#include "DirectXTK/Inc/SpriteFont.h"
#include "DirectXTK/Inc/DDSTextureLoader.h"


const float FRAME_BUFFER_W = 1920.0f;				//�t���[���o�b�t�@�̕��B
const float FRAME_BUFFER_H = 1080.0f;				//�t���[���o�b�t�@�̍����B

//Effekseer�̃w�b�_�[�t�@�C�����C���N���[�h�B
#include "Effekseer.h"
#include "EffekseerRendererDX11.h"

#include "GameObject/IGameObject.h"

#include "math/Vector.h"
#include "math/Matrix.h"
#include "physics/Physics.h"
#include "HID/Pad.h"



#include "graphics/GraphicsEngine.h"

#include "graphics/Skeleton.h"

#include "graphics/animation/Animation.h"
#include "graphics/animation/AnimationClip.h"
#include "graphics/Camera.h"



static const int MAX_BONE = 512;	//!<�{�[���̍ő吔�B


#include "GameObject/GameObjectManager.h"
#include "graphics/2D/SpriteRender.h"
#include "graphics/SkinModelRender.h"
#include "ShadowMap.h"
#include "graphics/RenderTarget.h"
#include "graphics/ChangeRenderTarget.h"
#include "Timer/GameTime.h"
#include "Timer/Stopwatch.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "SkyCube/Sky.h"
#include "Light/PointLight.h"
#include "Light/LightManager.h"
#include "Light/LightBase.h"
#include "Light/DirectionLight.h"

#include "Effekseer.h"
#include "EffekseerRendererDX11.h"

#include "graphics/Effect/Effect.h"
using namespace ksEngine;