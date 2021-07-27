#include "stdafx.h"
#include "EffectEngine.h"
#include "graphics/PresetRenderState.h"

static const int MRT_MAX = 8;
void EffectEngine::Release()
{
	if (m_manager != nullptr) {
		m_manager->Destroy();
		m_manager = nullptr;
	}
	if (m_renderer != nullptr) {
		m_renderer->Destroy();
		m_renderer = nullptr;
	}
	if (m_finalCombineAddBlendState != nullptr) {
		m_finalCombineAddBlendState->Release();
		m_finalCombineAddBlendState = nullptr;
	}
	m_resourcetManager.Release();
	m_fullscreenQuad.Release();
}

void EffectEngine::Init()
{
	Release();
	//レンダラーを初期化
	m_renderer = EffekseerRendererDX11::Renderer::Create(
		g_graphicsEngine->GetD3DDevice(),
		g_graphicsEngine->GetD3DDeviceContext(),
		2000
	);

	//エフェクトマネージャを初期化
	m_manager = Effekseer::Manager::Create(10000);

	//描画用インスタンスから描画機能を設定
	m_manager->SetSpriteRenderer(m_renderer->CreateSpriteRenderer());
	m_manager->SetRibbonRenderer(m_renderer->CreateRibbonRenderer());
	m_manager->SetRingRenderer(m_renderer->CreateRingRenderer());
	m_manager->SetTrackRenderer(m_renderer->CreateTrackRenderer());
	m_manager->SetModelRenderer(m_renderer->CreateModelRenderer());

	//描画用インスタンスからテクスチャの読み込み機能を設定
	//独自拡張可能、現在はファイルから読みこんでいる
	m_manager->SetTextureLoader(m_renderer->CreateTextureLoader());
	m_manager->SetModelLoader(m_renderer->CreateModelLoader());

	GraphicsEngine*& ge = g_graphicsEngine;
	m_addEffectBuffer.Create(
		FRAME_BUFFER_W,
		FRAME_BUFFER_H,
		DXGI_FORMAT_R8G8B8A8_UNORM
	);
	m_addEffectBuffer.SetDepthStencilView(ge->GetDepthStencilView());

	m_renderFlags.resize(1024);
	m_copyVS.Load("Assets/shader/copy.fx", "VSMain", ksEngine::Shader::EnType::VS);
	m_copyPS.Load("Assets/shader/copy.fx", "PSMain", ksEngine::Shader::EnType::PS);

	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));
	ID3D11Device* pd3d = ge->GetD3DDevice();

	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_COLOR;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_RED | D3D11_COLOR_WRITE_ENABLE_BLUE | D3D11_COLOR_WRITE_ENABLE_GREEN;
	pd3d->CreateBlendState(&blendDesc, &m_finalCombineAddBlendState);

	InitPrimitive();

	//どんなバッファを作成するのかをせてbufferDescに設定する。
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));				//０でクリア。
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;						//バッファで想定されている、読み込みおよび書き込み方法。
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;			//バッファをどのようなパイプラインにバインドするかを指定する。
																//定数バッファにバインドするので、D3D11_BIND_CONSTANT_BUFFERを指定する。
	bufferDesc.CPUAccessFlags = 0;								//CPU アクセスのフラグです。

	bufferDesc.ByteWidth = sizeof(CVector4);
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_cb);														//CPUアクセスが不要な場合は0。
}


void EffectEngine::Update()
{
	//カメラ行列を設定。
	m_renderer->SetCameraMatrix(g_camera3D.GetViewMatrix());
	m_renderer->SetProjectionMatrix(g_camera3D.GetProjectionMatrix());

	m_manager->Update(gameTime().GetFrameDeltaTime() / (1.0f / 60.0f));
}

void EffectEngine::Render()
{
	m_renderer->BeginRendering();
	m_manager->Draw();
	m_renderer->EndRendering();


	//ID3D11DeviceContext* devCon = g_graphicsEngine->GetD3DDeviceContext();
	////現在のレンダリングターゲットをバックアップする。
	//D3D11_VIEWPORT oldViewPorts;
	//UINT NumView = 1;
	//devCon->RSGetViewports(&NumView, &oldViewPorts);
	////unsigned int numRenderTargetViews;
	//devCon->OMGetRenderTargets(
	//	1, 
	//	&m_oldRenderTargetView,
	//	&m_oldDepthStencilView);

	//using namespace Effekseer;
	//auto nodeCount = 0;
	//m_manager->QueryNode([&](EffectNode* node) {
	//	EffectBasicRenderParameter param = node->GetBasicRenderParameter();
	//	m_renderFlags[nodeCount] = node->GetRenderFlag();	//元々の描画フラグをバックアップする。
	//	nodeCount++;
	//});
	//{
	//	//加算物以外は通常レンダリング。
	//	nodeCount = 0;
	//	m_manager->QueryNode([&](EffectNode* node) {
	//		EffectBasicRenderParameter param = node->GetBasicRenderParameter();
	//		if (param.AlphaBlend == AlphaBlendType::Add) {
	//			//加算物は描画しない。
	//			node->SetRenderFlag(false);
	//		}
	//	});

	//	m_renderer->BeginRendering();
	//	m_manager->Draw();
	//	m_renderer->EndRendering();
	//}
	//{
	//	//続いて加算物。
	//	nodeCount = 0;
	//	m_manager->QueryNode([&](EffectNode* node) {
	//		EffectBasicRenderParameter param = node->GetBasicRenderParameter();
	//		if (param.AlphaBlend == AlphaBlendType::Add) {
	//			//加算物の描画フラグを戻す。
	//			node->SetRenderFlag(m_renderFlags[nodeCount]);
	//		}
	//		else {
	//			//加算物以外は描画しない。
	//			node->SetRenderFlag(false);
	//		}
	//		nodeCount++;
	//	});

	//	//加算物はオフスクリーンレンダリングを行って、後で合成する。
	//	RenderTarget* renderTargets[] = {
	//		&m_addEffectBuffer
	//	};
	//	ID3D11RenderTargetView* copyTarget = renderTargets[0]->GetRenderTargetView();
	//	ID3D11DepthStencilView* copyDepth = renderTargets[0]->GetDepthStensilView();
	//	devCon->OMSetRenderTargets(
	//		1, 
	//		&copyTarget,
	//		copyDepth
	//	);
	//	float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f }; //red,green,blue,alpha
	//	devCon->ClearRenderTargetView(copyTarget, ClearColor);

	//	//加算物を描画する。
	//	m_renderer->BeginRendering();
	//	m_manager->Draw();
	//	m_renderer->EndRendering();

	//	//レンダリングターゲットを差し戻す。
	//	devCon->OMSetRenderTargets(1, &m_oldRenderTargetView,m_oldDepthStencilView);
	//	CVector2 uvOffset;
	//	uvOffset.x = 0.5f / oldViewPorts.Width;
	//	uvOffset.y = 0.5f / oldViewPorts.Height;
	//	devCon->UpdateSubresource(m_cb, 0, nullptr, &uvOffset, 0, 0);
	//	devCon->PSSetConstantBuffers(0,1, &m_cb);
	//	ID3D11ShaderResourceView* textures[1] = { m_addEffectBuffer.GetRenderTargetSRV() };
	//	devCon->PSSetShaderResources(0,1, textures);
	//	devCon->PSSetShader((ID3D11PixelShader*)m_copyPS.GetBody(), NULL, 0);
	//	devCon->VSSetShader((ID3D11VertexShader*)m_copyVS.GetBody(), NULL, 0);

	//	ID3D11DepthStencilState* oldDepthStencil = nullptr;
	//	devCon->OMGetDepthStencilState(&oldDepthStencil,(UINT)0);
	//	ID3D11RasterizerState* oldRSState = nullptr;
	//	devCon->RSGetState(&oldRSState);
	//	ID3D11BlendState* oldBlendState = nullptr;
	//	UINT Mask = 0xffffff;
	//	devCon->OMGetBlendState(&oldBlendState, NULL, &Mask);

	//	devCon->RSSetState(RasterizerState::spriteRender);
	//	devCon->OMSetDepthStencilState(DepthStencilState::disable,0);
	//	float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	//	devCon->OMSetBlendState(m_finalCombineAddBlendState,
	//		blendFactor, //ブレンディングファクター。気にしなくてよい
	//		0xffffffff //サンプリングマスク。気にしなくてよい。
	//	);

	//	m_fullscreenQuad.Draw();

	//	//戻す。
	//	devCon->OMSetDepthStencilState(oldDepthStencil,0);
	//	devCon->RSSetState(oldRSState);
	//	devCon->OMSetBlendState(oldBlendState,
	//		blendFactor, //ブレンディングファクター。気にしなくてよい
	//		0xffffffff //サンプリングマスク。気にしなくてよい。
	//	);

	//}
}

Effekseer::Effect * EffectEngine::CreateEffekseerEffect(const wchar_t * filePath)
{
	return Effekseer::Effect::Create(m_manager, (const EFK_CHAR*)filePath);
}

Effekseer::Handle EffectEngine::Play(Effekseer::Effect * effect)
{
	return  m_manager->Play(effect, 0, 0, 0);
}

void EffectEngine::Stop(Effekseer::Handle handle)
{
	m_manager->StopEffect(handle);
}

void EffectEngine::DrawPrimitive()
{
	m_fullscreenQuad.Draw();
}

void EffectEngine::InitPrimitive()
{
	//頂点バッファのソースデータ。
	SSimpleVertex vertices[] =
	{
		{
			CVector4(-1.0f, -1.0f, 0.0f, 1.0f),
			CVector2(0.0f, 1.0f),
		},
		{
			CVector4(1.0f, -1.0f, 0.0f, 1.0f),
			CVector2(1.0f, 1.0f),
		},
		{
			CVector4(-1.0f, 1.0f, 0.0f, 1.0f),
			CVector2(0.0f, 0.0f)
		},
		{
			CVector4(1.0f, 1.0f, 0.0f, 1.0f),
			CVector2(1.0f, 0.0f)
		}

	};
	short indices[] = { 0,1,2,3 };

	m_fullscreenQuad.Create(
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
		4,
		sizeof(SSimpleVertex),
		vertices,
		4,
		IndexBuffer::enIndexType_16,
		indices
	);
}
