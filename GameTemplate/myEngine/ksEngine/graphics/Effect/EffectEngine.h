#pragma once
#include "ResourceManager.h"
#include "Primitive.h"
class RenderTarget;
using EffectResourceManager = ResourceManager<Effekseer::Effect>;
class EffectEngine
{
public:
	EffectEngine(){}
	~EffectEngine(){
		Release();
	}
	/// <summary>
	/// ���
	/// </summary>
	void Release();
	/// <summary>
	/// ������
	/// </summary>
	void Init();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	void Render();
	/// <summary>
	/// Effecseer�̃G�t�F�N�g���쐬
	/// </summary>
	Effekseer::Effect* CreateEffekseerEffect(const wchar_t* filePath);
	/// <summary>
	/// Effekseer�̃G�t�F�N�g���Đ�
	/// </summary>
	Effekseer::Handle Play(Effekseer::Effect* effect);
	/// <summary>
	/// Effekseer�}�l�[�W���[�̎擾
	/// </summary>
	Effekseer::Manager& GetEffekseerManager() {
		return *m_manager;
	}
	/// <summary>
	/// Effekseer�̃G�t�F�N�g�̒�~
	/// </summary>
	void Stop(Effekseer::Handle handle);
	/// <summary>
	/// ���\�[�X�}�l�[�W���[���擾
	/// </summary>
	EffectResourceManager& GetResourceManager() {
		return m_resourcetManager;
	}
	void DrawPrimitive();
private:
	void InitPrimitive();
private:
	EffectResourceManager m_resourcetManager;//
	Effekseer::Manager* m_manager = nullptr;
	EffekseerRenderer::Renderer*m_renderer = nullptr; 
	RenderTarget m_addEffectBuffer;
	std::vector<int> m_renderFlags;
	ID3D11BlendState*m_finalCombineAddBlendState = nullptr;
	ID3D11Buffer* m_cb = nullptr;
	ksEngine::Shader m_copyVS;//�R�s�[�p�̒��_�V�F�[�_�[
	ksEngine::Shader m_copyPS;//�R�s�[�p�̃s�N�Z���V�F�[�_�[

	ID3D11RenderTargetView* m_oldRenderTargetView = nullptr;
	ID3D11DepthStencilView* m_oldDepthStencilView = nullptr;
	Primitive m_fullscreenQuad;
};

