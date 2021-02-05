#pragma once
class PostEffect;
#include "Shader.h"
#include "GaussianBlur.h"
class Bloom
{
public:
	Bloom();
	~Bloom();

	void Init();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw(PostEffect& postEffect);

private:
	/// <summary>
	/// アルファブレンディングのステートを初期化する。
	/// </summary>
	void InitAlphaBlendState();
	/// <summary>
	/// 定数バッファの初期化。
	/// </summary>
	//void InitConstantBuffer();
	/// <summary>
	/// シェーダーを初期化。
	/// </summary>
	void InitShader();
	/// <summary>
	/// レンダリングターゲットの初期化。
	/// </summary>
	void InitRenderTarget();
	/// <summary>
	/// サンプラステートの初期化。
	/// </summary>
	void InitSamplerState();
private:
	static const int NUM_DOWN_SAMPLE = 4;
	//static const int NUM_WEIGHTS = 8;	//カウスフィルタの重みの数。
	/*!
	* @brief	ブラー用のパラメータバッファ。
	*@details
	* これを変更したら、Assets/shader/bloom.fxのCBBlurの中身も変更するように。
	*/
	//struct SBlurParam {
	//	CVector4 offset;
	//	float weights[NUM_WEIGHTS];
	//};
	RenderTarget m_luminanceRT;			//輝度を抽出するレンダリングターゲット
	//RenderTarget m_downSamplingRT[2];	//ブラーをかけるためのダウンサンプリング用のレンダリングターゲット。
	ksEngine::Shader m_vs;						//何もしない頂点シェーダー。
	ksEngine::Shader m_psLuminance;				//輝度抽出用のピクセルシェーダー。
	//ksEngine::Shader m_vsXBlur;					//Xブラー用の頂点シェーダー。
	//ksEngine::Shader m_vsYBlur;					//Yブラー用の頂点シェーダー。
	//ksEngine::Shader m_psBlur;					//ブラー用のピクセルシェーダー。
	ksEngine::Shader m_psFinal;					//最終合成用のピクセルシェーダー。
	ID3D11BlendState* m_disableBlendState = nullptr;	//アルファブレンディングを無効にするブレンディングステート。
	ID3D11BlendState* m_finalBlendState = nullptr;		//最終合成用のブレンディングステート。

	//SBlurParam m_blurParam;				//ブラー用のパラメータ。
	//ID3D11Buffer* m_blurParamCB = nullptr;	//ブラーパラメータ用の定数バッファ。
	//float m_blurDispersion = 50.0f;		//ブラーの分散具合。大きくするほど強く分散する。
	ID3D11SamplerState* m_samplerState = nullptr;		//サンプラステート。
	GaussianBlur m_gaussianBlur[NUM_DOWN_SAMPLE];
};

