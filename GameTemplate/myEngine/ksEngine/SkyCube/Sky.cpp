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
	//�Q�ƃJ�E���^���グ�Ă����Ȃ��ƁA����ς݂̃e�N�X�`���ɃA�N�Z�X�����Ⴄ�B
	m_srv->AddRef();
	auto device = g_graphicsEngine->GetD3DDevice();	
	
	
	////��������ID3D11Texture2D�̏��
	//D3D11_TEXTURE2D_DESC desc = {};
	//desc.Width = 256;
	//desc.Height = 128;
	//desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	//desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//desc.MipLevels = 1;
	//desc.ArraySize = 1;
	//desc.SampleDesc.Count = 1;
	////�摜�f�[�^��K���ɐ���
	////�ݒ肷��l��desc.Format�ɍ��������̂ɂ��邱��
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
	//initData.SysMemPitch = sizeof(rawData[0]) * desc.Width;//1�s������̃f�[�^��
	//initData.SysMemSlicePitch = sizeof(rawData[0]) * desc.Width * desc.Height;//�����ł͑S�̂̃T�C�Y
	////�e�N�X�`����\��ID3D11Texture2D�̍쐬
	//auto thr = device->CreateTexture2D(&desc, &initData, &textur);
	//if (FAILED(thr)) {
	//	throw std::runtime_error("ID3D11Texture�̍쐬�Ɏ��s");
	//}






	ID3D11Texture2D* textur = nullptr;
	//m_srv->GetResource((ID3D11Resource**)&textur);

	if (textur != nullptr) {
		D3D11_TEXTURE2D_DESC texDesc;
		textur->GetDesc(&texDesc); 
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		ZeroMemory(&srvDesc, sizeof(srvDesc));
 		srvDesc.Format = texDesc.Format;
		//�e�N�X�`���z��B
		//todo �Ƃ肠�����L���[�u�}�b�v�Œ�ŁE�E�E
		srvDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURECUBE;
		srvDesc.TextureCube.MipLevels = texDesc.MipLevels;
		srvDesc.TextureCube.MostDetailedMip = 0;
		g_graphicsEngine->GetD3DDevice()->CreateShaderResourceView(textur, &srvDesc, &m_srv);
	}
	m_psSkyShader.Load("Assets/shader/model.fx", "PSMain_SkyCube", Shader::EnType::PS);
	//�}�e���A���ɃN�G���������āA�V�F�[�_�[�ƃe�N�X�`���������ւ��邺�B
	m_skinModelRender->FindMaterial([&](ModelEffect* mat) {
		mat->SetRender3DModelPSShader(m_psSkyShader);
		mat->SetDiffuseTexture(m_srv);
	});
	//����͕K���X�V���s���B
	m_isDirty = true;
	return true;
}

void ksEngine::Sky::Update()
{
	if (m_isDirty == true) {
		//�X�V�̕K�v����B
		m_skinModelRender->SetScale(m_scale);
		m_skinModelRender->SetPosition(m_position);
		m_skinModelRender->SetAmbientColor(m_AmbientColor);
		m_isDirty = false;
	}
}
