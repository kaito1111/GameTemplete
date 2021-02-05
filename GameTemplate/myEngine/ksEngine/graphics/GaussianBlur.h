#pragma once
#include "graphics/GPUBuffer/ConstantBufferGPU.h"
#include "Shader.h"
class GaussianBlur
{
public:
	GaussianBlur();
	~GaussianBlur();

	/// <summary>
	/// 初期化。
	/// </summary>
	/// <param name="srcTexture">ブラーをかけるテクスチャのSRV</param>
	/// <param name="blurIntensity">ブラーの強さ。値が大きいほど強くブラーがかかる。</param>
	void Init(ID3D11ShaderResourceView* srcTextureSRV, float blurIntensity);
	/// <summary>
	/// ブラーの実行
	/// </summary>
	/// <param name="postEffect">
	/// ポストエフェクトのインスタンス。
	/// 全画面描画の機能を使いたいだけです。。。
	/// </param>
	/// <remarks>
	/// Init関数を呼び出した後で実行するようにしてください。
	/// </remarks>
	void Execute(PostEffect& postEffect);

	ID3D11ShaderResourceView* GetResultTextureSRV() {
		return m_renderTarget[enRenderTarget_YBlur].GetRenderTargetSRV();
	}
private:
	/// <summary>
	/// ブラーの重みの更新。
	/// </summary>
	void UpdateWeights();
private:
	static const int NUM_WEIGHTS = 8;	//カウスフィルタの重みの数。
	/// <summary>
	/// ブラー用のパラメータバッファ。
	/// </summary>
	/// <remarks>
	/// これを変更したら、Assets/shader/GaussianBlur.fxのCBBlurの中身も変更するように。
	/// </remarks>
	struct SBlurParam {
		float weights[NUM_WEIGHTS];
	};
	ID3D11ShaderResourceView* m_SrcTextureSRV = nullptr;//ソーステクスチャのSRV
	float m_BlurIntensity = 25.0f;						//ブラーの強さ。ブラーのウェイトの計算で使用されます。
	bool m_IsCreate = false;
	unsigned int m_srcTextureWidth = 0;
	unsigned int m_srcTextureHight = 0;
	ksEngine::Shader m_vsXBlur;
	ksEngine::Shader m_vsYBlur;
	ksEngine::Shader m_psBlur;
	SBlurParam m_blurParam;
	ID3D11SamplerState* m_samplerState=nullptr;
	/// <summary>
	/// レンダリングターゲット。
	/// </summary>
	enum EnRenderTarget {
		enRenderTarget_XBlur,		//Xブラーの書き込み先となるレンダリングターゲット。
		enRenderTarget_YBlur,		//Yブラーの書き込み先となるレンダリングターゲット。
		enRenderTarget_Num,			//レンダリングターゲットの枚数。
	};
	RenderTarget m_renderTarget[enRenderTarget_Num];		//レンダリングターゲット。
	ConstantBufferGPU m_blurCbGPU;
};