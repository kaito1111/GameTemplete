#pragma once

#include "graphics/Shader.h"
#include <array>

/*!
*@brief	���f���G�t�F�N�g�B
*/
class ModelEffect : public DirectX::IEffect {
protected:
	std::wstring m_materialName;	//!<�}�e���A�����B
	ksEngine::Shader* m_pVSShader = nullptr;
	ksEngine::Shader* m_pPSShader = nullptr;
	ksEngine::Shader m_vsShader;
	ksEngine::Shader m_psShader;
	ksEngine::Shader m_vsShadowMap;			//�V���h�E�}�b�v�����p�̒��_�V�F�[�_�[�B
	ksEngine::Shader m_psShadowMap;			//�V���h�E�}�b�v�����p�̃s�N�Z���V�F�[�_�[�B
	bool isSkining;
	ksEngine::Shader m_psSilhouette;		//�V���G�b�g�`��p�̃s�N�Z���V�F�[�_�[�B
	int m_RenderMode = 0;
	ID3D11DepthStencilState* m_silhouettoDepthStepsilState = nullptr;	//�V���G�b�g�`��p�̃f�v�X�X�e���V���X�e�[�g�B
	ID3D11ShaderResourceView* m_albedoTexture = nullptr;
	std::array<ID3D11ShaderResourceView*, 4> m_albedoTextureStack = { nullptr };
	int m_albedoTextureStackPos = 0;
	ID3D11DepthStencilView* m_depthStencilView;

	ID3D11ShaderResourceView* m_ShadowMapTexture = nullptr;
public:
	ModelEffect()
	{
		m_psShader.Load("Assets/shader/model.fx", "PSMain", ksEngine::Shader::EnType::PS);
		
		m_pPSShader = &m_psShader;

		auto dv = g_graphicsEngine->GetD3DDevice();

		//�쐬����[�x�X�e���V���X�e�[�g�̒�`��ݒ肵�Ă����B
		D3D11_DEPTH_STENCIL_DESC desc = { 0 };
		desc.DepthEnable = true;
		desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		desc.DepthFunc = D3D11_COMPARISON_GREATER;

		dv->CreateDepthStencilState(&desc, &m_silhouettoDepthStepsilState);

		m_psSilhouette.Load("Assets/shader/model.fx", "PSMain_Silhouette", ksEngine::Shader::EnType::PS);

		m_vsShadowMap.Load("Assets/shader/model.fx", "VSMain_ShadowMap", ksEngine::Shader::EnType::VS);
		m_psShadowMap.Load("Assets/shader/model.fx", "PSMain_ShadowMap", ksEngine::Shader::EnType::PS);
	}
	virtual ~ModelEffect()
	{
		if (m_albedoTexture != nullptr) {
			m_albedoTexture->Release();
		}
		if (m_silhouettoDepthStepsilState != nullptr) {
			m_silhouettoDepthStepsilState->Release();
		}
	}
	void __cdecl Apply(ID3D11DeviceContext* deviceContext) override;

	void __cdecl GetVertexShaderBytecode(void const** pShaderByteCode, size_t* pByteCodeLength) override
	{
		*pShaderByteCode = m_vsShader.GetByteCode();
		*pByteCodeLength = m_vsShader.GetByteCodeSize();
	}
	void SetMatrialName(const wchar_t* matName)
	{
		m_materialName = matName;
	}
	
	bool EqualMaterialName(const wchar_t* name) const
	{
		return wcscmp(name, m_materialName.c_str()) == 0;
	}
	
	void SetRenderMode(int rm) {
		m_RenderMode = rm;
	}
	void SetAlbedoTexture(ID3D11ShaderResourceView* texSRV)
	{
		if (m_albedoTexture != nullptr) {
			//�Q�ƃJ�E���^��������B
			m_albedoTexture->Release();
		}
		m_albedoTexture = texSRV;
		//�Q�ƃJ�E���^���グ��B
		m_albedoTexture->AddRef();
	}
	void PushAlbedoTexture()
	{
		m_albedoTextureStack[m_albedoTextureStackPos] = m_albedoTexture;
		m_albedoTexture = nullptr;
		m_albedoTextureStackPos++;
	}
	void PopAlbedoTexture()
	{
		m_albedoTextureStackPos--;
		SetAlbedoTexture(m_albedoTextureStack[m_albedoTextureStackPos]);
	}

	void SetRender3DModelPSShader(ksEngine::Shader& psShader)
	{
		m_pPSShader = &psShader;
	}
	void SetDiffuseTexture(ID3D11ShaderResourceView* tex)
	{
		m_albedoTexture = tex;
	}
};
/*!
*@brief
*  �X�L���Ȃ����f���G�t�F�N�g�B
*/
class NonSkinModelEffect : public ModelEffect {
public:
	NonSkinModelEffect()
	{
		m_vsShader.Load("Assets/shader/model.fx", "VSMain", ksEngine::Shader::EnType::VS);
		m_pVSShader = &m_vsShader;
		isSkining = false;
	}
};
/*!
*@brief
*  �X�L�����f���G�t�F�N�g�B
*/
class SkinModelEffect : public ModelEffect {
public:
	SkinModelEffect()
	{
		wchar_t hoge[256];
		GetCurrentDirectoryW(256, hoge);
		m_vsShader.Load("Assets/shader/model.fx", "VSMainSkin", ksEngine::Shader::EnType::VS);
		m_pVSShader = &m_vsShader;
		isSkining = true;
	}
};

/*!
*@brief
*  �G�t�F�N�g�t�@�N�g���B
*/
class SkinModelEffectFactory : public DirectX::EffectFactory {
public:
	SkinModelEffectFactory(ID3D11Device* device) :
		EffectFactory(device) {}
	std::shared_ptr<DirectX::IEffect> __cdecl CreateEffect(const EffectInfo& info, ID3D11DeviceContext* deviceContext)override
	{
		std::shared_ptr<ModelEffect> effect;
		if (info.enableSkinning) {
			//�X�L�j���O����B
			effect = std::make_shared<SkinModelEffect>();
		}
		else {
			//�X�L�j���O�Ȃ��B
			effect = std::make_shared<NonSkinModelEffect>();
		}
		effect->SetMatrialName(info.name);
		if (info.diffuseTexture && *info.diffuseTexture) 
		{
			ID3D11ShaderResourceView* texSRV;
			DirectX::EffectFactory::CreateTexture(info.diffuseTexture, deviceContext, &texSRV);
			effect->SetAlbedoTexture(texSRV);
		}
		return effect;
	}

	void __cdecl CreateTexture(const wchar_t* name, ID3D11DeviceContext* deviceContext, ID3D11ShaderResourceView** textureView) override
	{
		return DirectX::EffectFactory::CreateTexture(name, deviceContext, textureView);
	}
};
