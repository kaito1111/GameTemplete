#include "stdafx.h"
#include "Bloom.h"
#include "PostEffect.h"
Bloom::Bloom()
{
}

Bloom::~Bloom()
{
	if (m_disableBlendState != nullptr) {
		m_disableBlendState->Release();
	}
	//if (m_blurParamCB != nullptr) {
	//	m_blurParamCB->Release();
	//}
	//if (m_samplerState != nullptr) {
	//	m_samplerState->Release();
	//}
	if (m_finalBlendState != nullptr) {
		m_finalBlendState->Release();
	}
}

void Bloom::Init()
{
	InitRenderTarget();

	InitShader();

	InitAlphaBlendState();

	//InitConstantBuffer();

	InitSamplerState();

	//輝度テクスチャをぼかすためのガウシアンブラーを初期化する。
	ID3D11ShaderResourceView* srcBlurTexture = m_luminanceRT.GetRenderTargetSRV();
	for (int i = 0; i < NUM_DOWN_SAMPLE; i++) {
		m_gaussianBlur[i].Init(srcBlurTexture, 25.0f);
		//次のガウスブラーで使用するソーステクスチャを設定する。
		srcBlurTexture = m_gaussianBlur[i].GetResultTextureSRV();
	}
}

void Bloom::InitAlphaBlendState()
{
	CD3D11_DEFAULT defaultSettings;
	//デフォルトセッティングで初期化する。
	CD3D11_BLEND_DESC blendDesc(defaultSettings);
	auto device = g_graphicsEngine->GetD3DDevice();

	device->CreateBlendState(&blendDesc, &m_disableBlendState);

	//最終合成用のブレンドステートを作成する。
	//最終合成は加算合成。
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	device->CreateBlendState(&blendDesc, &m_finalBlendState);
}

//void Bloom::InitConstantBuffer()
//{
//	D3D11_BUFFER_DESC desc;
//
//	ZeroMemory(&desc, sizeof(desc));
//	desc.Usage = D3D11_USAGE_DEFAULT;
//	desc.ByteWidth = (((sizeof(SBlurParam) - 1) / 16) + 1) * 16;	//16バイトアライメントに切りあげる。
//	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//	desc.CPUAccessFlags = 0;
//	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&desc, NULL, &m_blurParamCB);
//}

void Bloom::InitShader()
{
	m_vs.Load("Assets/shader/bloom.fx", "VSMain", ksEngine::Shader::EnType::VS);
	m_psLuminance.Load("Assets/shader/bloom.fx", "PSSamplingLuminance", ksEngine::Shader::EnType::PS);
	//m_vsXBlur.Load("Assets/shader/bloom.fx", "VSXBlur", ksEngine::Shader::EnType::VS);
	//m_vsYBlur.Load("Assets/shader/bloom.fx", "VSYBlur", ksEngine::Shader::EnType::VS);
	//m_psBlur.Load("Assets/shader/bloom.fx", "PSBlur", ksEngine::Shader::EnType::PS);
	m_psFinal.Load("Assets/shader/bloom.fx", "PSFinal", ksEngine::Shader::EnType::PS);
}

void Bloom::InitRenderTarget()
{
	//輝度抽出用のレンダリングターゲットを作成する。
	m_luminanceRT.Create(
		FRAME_BUFFER_W,
		FRAME_BUFFER_H,
		DXGI_FORMAT_R16G16B16A16_FLOAT
	);

	////ブラーをかけるためのダウンサンプリング用のレンダリングターゲットを作成。
	////横ブラー用。
	//m_downSamplingRT[0].Create(
	//	FRAME_BUFFER_W * 0.5f,	//横の解像度をフレームバッファの半分にする。
	//	FRAME_BUFFER_H,
	//	DXGI_FORMAT_R16G16B16A16_FLOAT
	//);
	////縦ブラー用。
	//m_downSamplingRT[1].Create(
	//	FRAME_BUFFER_W * 0.5f,	//横の解像度をフレームバッファの半分にする。
	//	FRAME_BUFFER_H * 0.5f,	//縦の解像度をフレームバッファの半分にする。
	//	DXGI_FORMAT_R16G16B16A16_FLOAT
	//);

}

void Bloom::InitSamplerState()
{
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &m_samplerState);
}

void Bloom::Draw(PostEffect & postEffect)
{
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
	deviceContext->PSSetSamplers(0, 1, &m_samplerState);
	//まずは輝度を抽出する。
	{
		//αブレンドを無効にする。
		float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
		deviceContext->OMSetBlendState(m_disableBlendState, blendFactor, 0xffffffff);

		//輝度抽出用のレンダリングターゲットに変更する。
		ChangeRenderTarget(
			m_luminanceRT.GetRenderTargetView(),
			m_luminanceRT.GetDepthStensilView(), 
			m_luminanceRT.GetViewport()
		);
		//レンダリングターゲットのクリア。
		float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		m_luminanceRT.ClearRenderTarget(clearColor);

		//シーンをテクスチャとする。
		auto mainRTTexSRV = postEffect.GetMainRenderTarget()->GetRenderTargetSRV();
		deviceContext->PSSetShaderResources(0, 1, &mainRTTexSRV);

		//フルスクリーン描画。
		postEffect.DrawFullScreenQuadPrimitive(m_vs, m_psLuminance);
	}

	for (int i = 0; i < NUM_DOWN_SAMPLE; i++) {
		m_gaussianBlur[i].Execute(postEffect);
	}
	
	//最後にぼかした絵を加算合成でメインレンダリングターゲットに合成して終わり。
	{
		auto MainrenderTarget = postEffect.GetMainRenderTarget();
		ChangeRenderTarget(
			MainrenderTarget->GetRenderTargetView(),
			MainrenderTarget->GetDepthStensilView(),
			MainrenderTarget->GetViewport(),
			false
		);

		for (int registerNo = 0; registerNo < NUM_DOWN_SAMPLE; registerNo++) {
			auto srv = m_gaussianBlur[registerNo].GetResultTextureSRV();
			deviceContext->PSSetShaderResources(registerNo, 1, &srv);
		}

		//加算合成用のブレンディングステートを設定する。
		float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
		deviceContext->OMSetBlendState(m_finalBlendState, blendFactor, 0xffffffff);
		//フルスクリーン描画。
		postEffect.DrawFullScreenQuadPrimitive(m_vs, m_psFinal);

		//ブレンディングステートを戻す。
		deviceContext->OMSetBlendState(m_disableBlendState, blendFactor, 0xffffffff);

	}
}