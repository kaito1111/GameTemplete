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
	//�����_�����O�^�[�Q�b�g�̐؂�ւ��B
	deviceContext->OMSetRenderTargets(1, rtTbl, depthView);
	if (viewport != nullptr) {
		//�r���[�|�[�g���w�肳��Ă�����A�r���[�|�[�g���ύX����B
		deviceContext->RSSetViewports(1, viewport);
	}

	if (IsClear == true) {
		//���C�������_�����O�^�[�Q�b�g���N���A����B
		float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		deviceContext->ClearRenderTargetView(targetView, clearColor);
	}
}