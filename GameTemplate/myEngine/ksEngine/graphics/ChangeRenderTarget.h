#pragma once
class ChangeRenderTarget
{
public:
	//�����_�[�^�[�Q�b�g�r���[�ƃf�v�X�X�e���V���r���[�����C���Ƃ���
	ChangeRenderTarget(ID3D11RenderTargetView* targetView, ID3D11DepthStencilView* depthView, D3D11_VIEWPORT* viewport, bool isClear = true);
	~ChangeRenderTarget() {};
};