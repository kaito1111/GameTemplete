#pragma once
class RenderTarget
{
public:
	RenderTarget();
	~RenderTarget();

	void OffScreenRendering();
	void OnScreenRendering();

	ID3D11ShaderResourceView* GetRTSRV(){
		return m_renderTargetSRV;
	}
private:
	ID3D11RenderTargetView*		m_oldRenderTargetView;
	ID3D11DepthStencilView*		m_oldDepthStencilView;
	ID3D11Texture2D*			m_renderTargetTex = nullptr;		//!<�����_�����O�^�[�Q�b�g�ƂȂ�e�N�X�`���B
	ID3D11RenderTargetView*		m_renderTargetView = nullptr;		//!<�����_�[�^�[�Q�b�g�r���[�B
	ID3D11ShaderResourceView*	m_renderTargetSRV = nullptr;		//!<�����_�����O�^�[�Q�b�g��SRV
	ID3D11Texture2D*			m_depthStencilTex = nullptr;		//!<�f�v�X�X�e���V���ƂȂ�e�N�X�`���B
	ID3D11DepthStencilView*		m_depthStencilView = nullptr;		//!<�f�v�X�X�e���V���r���[�B
};

