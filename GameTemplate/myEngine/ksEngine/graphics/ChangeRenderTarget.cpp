#include "stdafx.h"
#include "ChangeRenderTarget.h"

ChangeRenderTarget::ChangeRenderTarget(
	ID3D11RenderTargetView * targetView,
	ID3D11DepthStencilView * depthView,
	D3D11_VIEWPORT * viewport,
	bool IsClear)
{
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();

	ID3D11RenderTargetView* rtTbl[] = {
		targetView
	};
	//レンダリングターゲットの切り替え。
	deviceContext->OMSetRenderTargets(1, rtTbl, depthView);
	if (viewport != nullptr) {
		//ビューポートが指定されていたら、ビューポートも変更する。
		deviceContext->RSSetViewports(1, viewport);
	}

	if (IsClear == true) {
		//メインレンダリングターゲットをクリアする。
		float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		deviceContext->ClearRenderTargetView(targetView, clearColor);
	}
}