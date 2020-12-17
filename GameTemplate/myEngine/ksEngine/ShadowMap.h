#pragma once
class SkinModel;
#include "graphics/RenderTarget.h"
class ShadowMap
{
public:
	ShadowMap();
	~ShadowMap();
	void RegistShadowCaster(SkinModel* shadowCaster)
	{
		m_shadowCasters.push_back(shadowCaster);
	}

	ID3D11ShaderResourceView* GetSRV() {
		return m_shadowMapRT.GetRenderTargetSRV();
	}
	CMatrix GetLightViewMatrox() {
		return m_lightViewMatrix;
	}
	CMatrix GetLightProjMatrix() {
		return m_lightProjMatrix;
	}
	void Init();
	void UpdateShadowMap();
	void RenderToShadowMap();

private:
	void SaveRenderTarget();
	void BackUpRenderTarget();

	//���݂̃����_�����O�^�[�Q�b�g���o�b�N�A�b�v���Ă����B
	ID3D11RenderTargetView* m_oldRenderTargetView = nullptr;
	ID3D11DepthStencilView* m_oldDepthStencilView = nullptr;
	//�r���[�|�[�g���o�b�N�A�b�v������Ă����B
	unsigned int m_numViewport = 1;
	D3D11_VIEWPORT m_oldViewports;
	CVector3 m_lightCameraPosition = { 0.0f,500.0f,0.0f };//���C�g�J�����̎��_�B
	CVector3 m_lightCameraTarget = { 0.0f,0.0f,0.0f }; //���C�g�J�����̒����_�B
	CMatrix m_lightViewMatrix; //���C�g�r���[�s��B
	CMatrix m_lightProjMatrix; //���C�g�v���W�F�N�V�����s��B
	RenderTarget m_shadowMapRT; //�V���h�E�}�b�v��`�悷�郌���_�����O�^�[�Q�b�g�B
	std::vector<SkinModel*> m_shadowCasters;	//�V���h�E�L���X�^�[�̔z��B
};

