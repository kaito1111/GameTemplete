#include "stdafx.h"
#include "Sky.h"
#include "graphics/SkinModelEffect.h"

ksEngine::Sky::Sky()
{
}

ksEngine::Sky::~Sky()
{
	if (m_srv != nullptr) {
		m_srv->Release();
	}
	//textur->Release();
}

void ksEngine::Sky::OnDestroy()
{
	DeleteGO(m_skinModelRender);
}

bool ksEngine::Sky::Start()
{
	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init(m_skyModelFilePath.c_str());
	HRESULT hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), m_skyCubeMapFilePath.c_str(), 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &m_srv);
	//参照カウンタを上げておかないと、解放済みのテクスチャにアクセスしちゃう。
	m_srv->AddRef();
	auto device = g_graphicsEngine->GetD3DDevice();	
	
	
	////生成するID3D11Texture2Dの情報
	//D3D11_TEXTURE2D_DESC desc = {};
	//desc.Width = 256;
	//desc.Height = 128;
	//desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	//desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//desc.MipLevels = 1;
	//desc.ArraySize = 1;
	//desc.SampleDesc.Count = 1;
	////画像データを適当に生成
	////設定する値はdesc.Formatに合ったものにすること
	//std::vector<uint32_t> rawData;
	//rawData.resize(desc.Width * desc.Height);
	//for (auto y = 0; y < desc.Height; ++y) {
	//	for (auto x = 0; x < desc.Width; ++x) {
	//		auto index = y * desc.Width + x;
	//		if (index % 52 < 10) {
	//			rawData[index] = 0xff55ffff;
	//		}
	//		else {
	//			rawData[index] = 0xffff5555;
	//		}
	//	}
	//}
	//D3D11_SUBRESOURCE_DATA initData;
	//initData.pSysMem = rawData.data();
	//initData.SysMemPitch = sizeof(rawData[0]) * desc.Width;//1行当たりのデータ長
	//initData.SysMemSlicePitch = sizeof(rawData[0]) * desc.Width * desc.Height;//ここでは全体のサイズ
	////テクスチャを表すID3D11Texture2Dの作成
	//auto thr = device->CreateTexture2D(&desc, &initData, &textur);
	//if (FAILED(thr)) {
	//	throw std::runtime_error("ID3D11Textureの作成に失敗");
	//}






	ID3D11Texture2D* textur = nullptr;
	//m_srv->GetResource((ID3D11Resource**)&textur);

	if (textur != nullptr) {
		D3D11_TEXTURE2D_DESC texDesc;
		textur->GetDesc(&texDesc); 
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		ZeroMemory(&srvDesc, sizeof(srvDesc));
 		srvDesc.Format = texDesc.Format;
		//テクスチャ配列。
		//todo とりあえずキューブマップ固定で・・・
		srvDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURECUBE;
		srvDesc.TextureCube.MipLevels = texDesc.MipLevels;
		srvDesc.TextureCube.MostDetailedMip = 0;
		g_graphicsEngine->GetD3DDevice()->CreateShaderResourceView(textur, &srvDesc, &m_srv);
	}
	m_psSkyShader.Load("Assets/shader/model.fx", "PSMain_SkyCube", Shader::EnType::PS);
	//マテリアルにクエリをかけて、シェーダーとテクスチャを差し替えるぜ。
	m_skinModelRender->FindMaterial([&](ModelEffect* mat) {
		mat->SetRender3DModelPSShader(m_psSkyShader);
		mat->SetDiffuseTexture(m_srv);
	});
	//初回は必ず更新を行う。
	m_isDirty = true;
	return true;
}

void ksEngine::Sky::Update()
{
	if (m_isDirty == true) {
		//更新の必要あり。
		m_skinModelRender->SetScale(m_scale);
		m_skinModelRender->SetPosition(m_position);
		m_skinModelRender->SetAmbientColor(m_AmbientColor);
		m_isDirty = false;
	}
}
