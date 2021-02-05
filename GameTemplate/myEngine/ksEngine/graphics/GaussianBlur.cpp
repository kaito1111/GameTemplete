#include "stdafx.h"
#include "GaussianBlur.h"

GaussianBlur::GaussianBlur()
{
}

GaussianBlur::~GaussianBlur()
{
	if (m_samplerState != nullptr) {
		m_samplerState->Release();
	}
}

void GaussianBlur::Init(ID3D11ShaderResourceView * srcTextureSRV, float blurIntensity)
{
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &m_samplerState);

	//ソーステクスチャのSRVをコピー
	m_SrcTextureSRV = srcTextureSRV;
	//UpdateWeight関数で使用するので、ブラーの強さをメンバ変数に記憶しておく
	m_BlurIntensity = blurIntensity;

	//取得テクスチャから、テクスチャ情報を取得する。
	D3D11_TEXTURE2D_DESC texDesc;
	{
		//ソーステクスチャの情報を取得。
		ID3D11Texture2D* tex;
		//まず、SRVに関連付けされているテクスチャを取得する。
		srcTextureSRV->GetResource((ID3D11Resource**)&tex);
		tex->GetDesc(&texDesc);
		//テクスチャ情報を取得できたのでテクスチャの参照カウンタをおろす。
		tex->Release();
	}
	//ソーステクスチャの幅と高さを記憶しておく。
	m_srcTextureHight = texDesc.Height;
	m_srcTextureWidth = texDesc.Width;

	//Xブラー用のレンダーターゲットを作成
	m_renderTarget[enRenderTarget_XBlur].Create(
		texDesc.Width / 2,//横の解像度を半分にする。
		texDesc.Height,
		texDesc.Format
	);

	//Yブラー用のレンダリングターゲットを作成。
	m_renderTarget[enRenderTarget_YBlur].Create(
		texDesc.Width / 2,//横の解像度を半分にする。
		texDesc.Height / 2,//縦の解像度を半分にする。
		texDesc.Format
	);

	//シェーダーをロード。
	m_vsXBlur.Load("Assets/shader/GaussianBlur.fx", "VSXBlur", ksEngine::Shader::EnType::VS);
	m_vsYBlur.Load("Assets/shader/GaussianBlur.fx", "VSYBlur", ksEngine::Shader::EnType::VS);
	m_psBlur.Load("Assets/shader/GaussianBlur.fx", "PSBlur", ksEngine::Shader::EnType::PS);
	//VRCM上に定数バッファを作成。
	m_blurCbGPU.Create(nullptr, sizeof(SBlurParam));

	//作成済み
	m_IsCreate = true;
}

void GaussianBlur::UpdateWeights()
{
	//ガウスフィルタの重みを更新する。
	float total = 0;
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		m_blurParam.weights[i] = expf(-0.5f*(float)(i*i) / m_BlurIntensity);
		total += 2.0f*m_blurParam.weights[i];
	}
	//重みの合計で各重みを除算して、正規化する。
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		m_blurParam.weights[i] /= total;
	}
}

void GaussianBlur::Execute(PostEffect & postEffect)
{
	if (m_IsCreate == false) {
		//初期化忘れ
		return;
	}
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
	UpdateWeights();

	deviceContext->PSSetSamplers(0, 1, &m_samplerState);
	auto d3d11CbGpu = m_blurCbGPU.GetD3D11Buffer();
	deviceContext->UpdateSubresource(
		d3d11CbGpu, 0, nullptr, &m_blurParam, 0, 0);
	deviceContext->PSSetConstantBuffers(
		0, 1, &d3d11CbGpu);

	{
		ChangeRenderTarget(
			m_renderTarget[enRenderTarget_XBlur].GetRenderTargetView(),
			m_renderTarget[enRenderTarget_XBlur].GetDepthStensilView(),
			m_renderTarget[enRenderTarget_XBlur].GetViewport());
		deviceContext->VSSetShaderResources(0, 1, &m_SrcTextureSRV);
		deviceContext->PSSetShaderResources(0, 1, &m_SrcTextureSRV);

		postEffect.DrawFullScreenQuadPrimitive(m_vsXBlur, m_psBlur);
	}

	{

		ChangeRenderTarget(
			m_renderTarget[enRenderTarget_YBlur].GetRenderTargetView(),
			m_renderTarget[enRenderTarget_YBlur].GetDepthStensilView(),
			m_renderTarget[enRenderTarget_YBlur].GetViewport());
		auto srcTextrueSrv = m_renderTarget[enRenderTarget_XBlur].GetRenderTargetSRV();
		deviceContext->VSSetShaderResources(0, 1, &srcTextrueSrv);
		deviceContext->PSSetShaderResources(0, 1, &srcTextrueSrv);

		postEffect.DrawFullScreenQuadPrimitive(m_vsYBlur, m_psBlur);
	}
}
