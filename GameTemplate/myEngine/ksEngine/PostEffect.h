#pragma once
#include "graphics/ChangeRenderTarget.h"
#include "graphics/Bloom.h"
#include "graphics/2D/Sprite.h"
class PostEffect
{
public:
	PostEffect();
	~PostEffect();

	//������
	void Init();
	//�����_�[�^�[�Q�b�g��؂�ւ���
	void ChangeMainRendertTarget();
	//�����ꂽ���̂��h���[����
	void PostRender();

	void Draw();
	RenderTarget* GetMainRenderTarget() {
		return &m_mainRenderTarget;
	}
	void DrawFullScreenQuadPrimitive(ksEngine::Shader& vsShader, ksEngine::Shader& psShader);
private:
	Bloom	m_bloom;	//�u���[���B
						//�t���X�N���[���`��p�̃����o�ϐ��B
	ID3D11Buffer*	m_vertexBuffer = nullptr;		//���_�o�b�t�@�B
	D3D11_VIEWPORT m_mainViewports;			//�ύX�O�̃r���[�|�[�g�B
	RenderTarget m_mainRenderTarget;
	ksEngine::Sprite m_copyMainRtToFrameBufferSprite;
	D3D11_VIEWPORT m_PostEffectViewports;			//�|�X�g�G�t�F�N�g�p�̃r���[�|�[�g�B
	ID3D11RenderTargetView* m_PostEffectRenderTargetView = nullptr;	//�|�X�g�G�t�F�N�g�p�̃����_�����O�^�[�Q�b�g�r���[�B
	ID3D11DepthStencilView* m_PostEffectDepthStencilView = nullptr;	//�|�X�g�G�t�F�N�g�p�̃f�v�X�X�e���V���r���[�B
};

