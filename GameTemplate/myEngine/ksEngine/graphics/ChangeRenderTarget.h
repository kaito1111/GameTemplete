#pragma once
class ChangeRenderTarget
{
public:
	//レンダーターゲットビューとデプスステンシルビューをメインとする
	ChangeRenderTarget(ID3D11RenderTargetView* targetView, ID3D11DepthStencilView* depthView, D3D11_VIEWPORT* viewport, bool isClear = true);
	~ChangeRenderTarget() {};
};