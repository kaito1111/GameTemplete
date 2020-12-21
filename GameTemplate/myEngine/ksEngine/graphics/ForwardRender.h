#pragma once
class ForwardRender
{
public:
	ForwardRender();
	~ForwardRender();

	void Init();
	void BuckupRenderTarget();
	//�o�b�N�A�b�v�������̂�ǂ݂���
	//���łɃt�H���[�h�����_�[������
	void LoadAndDraw();
private:
	RenderTarget m_mainRenderTarget;		//���C�������_�����O�^�[�Q�b�g�B
	Sprite m_copyMainRtToFrameBufferSprite;
	D3D11_VIEWPORT m_frameBufferViewports;			//�t���[���o�b�t�@�̃r���[�|�[�g�B
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//�t���[���o�b�t�@�̃����_�����O�^�[�Q�b�g�r���[�B
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//�t���[���o�b�t�@�̃f�v�X�X�e���V���r���[�B
};