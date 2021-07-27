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
	/// 解放
	/// </summary>
	void Release();
	/// <summary>
	/// 初期化
	/// </summary>
	void Init();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Render();
	/// <summary>
	/// Effecseerのエフェクトを作成
	/// </summary>
	Effekseer::Effect* CreateEffekseerEffect(const wchar_t* filePath);
	/// <summary>
	/// Effekseerのエフェクトを再生
	/// </summary>
	Effekseer::Handle Play(Effekseer::Effect* effect);
	/// <summary>
	/// Effekseerマネージャーの取得
	/// </summary>
	Effekseer::Manager& GetEffekseerManager() {
		return *m_manager;
	}
	/// <summary>
	/// Effekseerのエフェクトの停止
	/// </summary>
	void Stop(Effekseer::Handle handle);
	/// <summary>
	/// リソースマネージャーを取得
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
	ksEngine::Shader m_copyVS;//コピー用の頂点シェーダー
	ksEngine::Shader m_copyPS;//コピー用のピクセルシェーダー

	ID3D11RenderTargetView* m_oldRenderTargetView = nullptr;
	ID3D11DepthStencilView* m_oldDepthStencilView = nullptr;
	Primitive m_fullscreenQuad;
};

